-- 1. Employee Management Module
CREATE TABLE Employees (
    emp_id NUMBER PRIMARY KEY,
    full_name VARCHAR2(100) NOT NULL,
    email VARCHAR2(100) UNIQUE,
    position VARCHAR2(50),
    department VARCHAR2(50),
    hire_date DATE,
    salary NUMBER(10, 2)
);

-- 2. Customer Management (Reports Module)
CREATE TABLE Customer_Reports (
    report_id NUMBER PRIMARY KEY,
    cust_name VARCHAR2(100),
    email VARCHAR2(100),
    phone VARCHAR2(20),
    address VARCHAR2(255),
    report_type VARCHAR2(50),
    report_date DATE,
    satisfaction_score NUMBER(3, 1)
);

-- 3. Waste Management Module
CREATE TABLE Waste_Logs (
    waste_id NUMBER PRIMARY KEY,
    waste_type VARCHAR2(50),
    category VARCHAR2(50),
    quantity_kg NUMBER(10, 2),
    collection_date TIMESTAMP,
    location VARCHAR2(255),
    status VARCHAR2(20)
);

-- 4. Vehicle Management Module
CREATE TABLE Vehicles (
    vehicle_id NUMBER PRIMARY KEY,
    plate_number VARCHAR2(20) UNIQUE NOT NULL,
    vehicle_type VARCHAR2(50),
    model VARCHAR2(50),
    fuel_type VARCHAR2(20),
    status VARCHAR2(20),
    next_maintenance DATE
);

-- 5. Machines (Equipment) Management Module
CREATE TABLE Equipments (
    machine_id NUMBER PRIMARY KEY,
    name VARCHAR2(100),
    machine_type VARCHAR2(50),
    location VARCHAR2(100),
    purchase_date DATE,
    status VARCHAR2(20)
);

-- Create sequence for machines
CREATE SEQUENCE equipments_seq START WITH 1 INCREMENT BY 1;

-- Create trigger to auto-generate machine_id
CREATE OR REPLACE TRIGGER equipments_id_trigger
BEFORE INSERT ON Equipments
FOR EACH ROW
BEGIN
  SELECT equipments_seq.NEXTVAL INTO :NEW.machine_id FROM dual;
END;
/

-- 6. Supplier Management Module
CREATE TABLE Suppliers (
    supplier_id NUMBER PRIMARY KEY,
    name VARCHAR2(100) NOT NULL,
    email VARCHAR2(100),
    phone VARCHAR2(20),
    product_type VARCHAR2(50),
    contract_date DATE,
    performance_rate NUMBER(3, 2)
);