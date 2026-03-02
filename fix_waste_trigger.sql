-- Run as user MANAR in SQL Developer
-- Fix trigger after renaming WASTE_ID -> ID

-- 1) Create sequence if missing
DECLARE
    seq_count NUMBER;
BEGIN
    SELECT COUNT(*) INTO seq_count
    FROM user_sequences
    WHERE sequence_name = 'WASTE_ID_SEQ';

    IF seq_count = 0 THEN
        EXECUTE IMMEDIATE 'CREATE SEQUENCE WASTE_ID_SEQ START WITH 1 INCREMENT BY 1 NOCACHE';
    END IF;
END;
/

-- 2) Sync sequence with current max ID
DECLARE
    current_max NUMBER;
    curr_val NUMBER;
BEGIN
    SELECT NVL(MAX(ID), 0) INTO current_max FROM WASTE;

    BEGIN
        EXECUTE IMMEDIATE 'SELECT WASTE_ID_SEQ.NEXTVAL FROM DUAL' INTO curr_val;
    EXCEPTION
        WHEN OTHERS THEN
            curr_val := 0;
    END;

    IF curr_val <= current_max THEN
        EXECUTE IMMEDIATE 'ALTER SEQUENCE WASTE_ID_SEQ INCREMENT BY ' || (current_max - curr_val + 1);
        EXECUTE IMMEDIATE 'SELECT WASTE_ID_SEQ.NEXTVAL FROM DUAL' INTO curr_val;
        EXECUTE IMMEDIATE 'ALTER SEQUENCE WASTE_ID_SEQ INCREMENT BY 1';
    END IF;
END;
/

-- 3) Recreate trigger with new column name ID
CREATE OR REPLACE TRIGGER TRG_WASTE_BI
BEFORE INSERT ON WASTE
FOR EACH ROW
BEGIN
    IF :NEW.ID IS NULL THEN
        SELECT WASTE_ID_SEQ.NEXTVAL INTO :NEW.ID FROM DUAL;
    END IF;
END;
/

-- 4) Enable trigger
ALTER TRIGGER TRG_WASTE_BI ENABLE;

-- 5) Verify trigger status
SELECT trigger_name, status
FROM user_triggers
WHERE trigger_name = 'TRG_WASTE_BI';
