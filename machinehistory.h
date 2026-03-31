#ifndef MACHINEHISTORY_H
#define MACHINEHISTORY_H

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QFrame>
#include <QWidget>
#include <QList>
#include <QSize>

// ─────────────────────────────────────────────────────────────────────────────
//  Data structures
// ─────────────────────────────────────────────────────────────────────────────

struct StatusSegment {
    QString   status;
    QDateTime from;
    QDateTime to;           // isNull() → still active (use current timestamp)
    qint64    durationSec;  // filled by loadTimeline()
    double    pct;          // filled by loadTimeline()
};

struct MachineInfo {
    QString id;
    QString name;
    QString currentStatus;   // from history (last new_value) or fallback from Machine.STATUS
    QString purchaseDate;    // fetched directly from Machine.PURCHASE_DATE
    QString lastModified;    // MAX(changed_at) from machine_history
    int     totalChanges = 0;
    QString mostFreqStatus;
};

// ─────────────────────────────────────────────────────────────────────────────
//  TimelineBar  —  horizontal painted status bar
// ─────────────────────────────────────────────────────────────────────────────
class TimelineBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineBar(QWidget *parent = nullptr);
    void setSegments(const QList<StatusSegment> &segs);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *) override;
    QSize minimumSizeHint() const override { return {600, 80}; }
    QSize sizeHint()        const override { return {900, 80}; }

private:
    QList<StatusSegment> m_segs;
    int                  m_hoverIdx = -1;

    static QColor colorForStatus(const QString &s);
    QList<QRectF> segRects() const;
};

// ─────────────────────────────────────────────────────────────────────────────
//  MachineHistory dialog
// ─────────────────────────────────────────────────────────────────────────────
class MachineHistory : public QDialog
{
    Q_OBJECT

public:
    explicit MachineHistory(const QString &machineId,
                            const QString &machineName,
                            QWidget       *parent = nullptr);

private slots:
    void onApplyFilters();
    void onClearFilters();
    void onExportPDF();

private:
    // core
    QString              m_machineId;
    QString              m_machineName;
    MachineInfo          m_info;
    QList<StatusSegment> m_segments;

    // summary labels
    QLabel *m_lblId;
    QLabel *m_lblPurchaseDate;   // replaces m_lblCreated
    QLabel *m_lblModified;
    QLabel *m_lblChanges;
    QLabel *m_lblStatus;
    QLabel *m_badgeFreq;

    // timeline
    TimelineBar *m_timeline;
    QLabel      *m_tlNoData;

    // filter controls
    QLineEdit     *m_fId;
    QComboBox     *m_fStatus;
    QDateTimeEdit *m_fFrom;
    QDateTimeEdit *m_fTo;

    // table
    QTableWidget *m_table;

    // ── build helpers
    void buildUi();
    QFrame  *buildSummary();
    QFrame  *buildTimeline();
    QFrame  *buildFilters();
    QFrame  *buildTable();
    QWidget *buildExportBar();

    // ── data helpers
    void loadAll();
    void loadMachineInfo();
    void loadTimeline();
    void loadTable(const QString &idF,
                   const QString &statusF,
                   const QDateTime &from,
                   const QDateTime &to);

    // ── export
    void writePDF(const QString &path);

    // ── style helpers
    static QFrame *makeCard(QWidget *parent = nullptr);
    static QLabel *makeTitle(const QString &text, QWidget *parent = nullptr);
    static QString badgeStyle(const QString &status);
    static QLabel *makeSummaryValue(const QString &init,
                                    QWidget *parent = nullptr);
};

#endif // MACHINEHISTORY_H