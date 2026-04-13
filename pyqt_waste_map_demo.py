import json
import sys

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)
from PyQt5.QtWebEngineWidgets import QWebEngineView


CITY_COORDS = {
    "tunis": (36.8065, 10.1815),
    "ariana": (36.8665, 10.1647),
    "nabeul": (36.4561, 10.7376),
    "sousse": (35.8256, 10.6084),
    "sfax": (34.7406, 10.7603),
    "bizerta": (37.2744, 9.8739),
    "monastir": (35.7643, 10.8113),
    "kairouan": (35.6781, 10.0963),
    "gabes": (33.8815, 10.0982),
    "beja": (36.7333, 9.1833),
}


class MapWindow(QMainWindow):
    def __init__(self, location_name: str, latitude: float, longitude: float, parent=None):
        super().__init__(parent)
        self.setWindowTitle(f"Map - {location_name}")
        self.resize(900, 600)

        self.web_view = QWebEngineView(self)
        self.setCentralWidget(self.web_view)

        html = self._build_map_html(location_name, latitude, longitude)
        self.web_view.setHtml(html)

    @staticmethod
    def _build_map_html(location_name: str, latitude: float, longitude: float) -> str:
        safe_name = json.dumps(location_name)

        return f"""
<!DOCTYPE html>
<html>
<head>
  <meta charset=\"utf-8\" />
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">
  <title>Waste Location Map</title>
  <link
    rel=\"stylesheet\"
    href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\"
    integrity=\"sha256-p4NxAoJBhIIN+hmNHrzRCf9tD/miZyoHS5obTRR9BMY=\"
    crossorigin=\"\"
  />
  <script
    src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"
    integrity=\"sha256-20nQCchB9co0qIjJZRGuk2/Z9VM+kNiyxNV1lvTlZBo=\"
    crossorigin=\"\"
  ></script>
  <style>
    html, body, #map {{
      margin: 0;
      padding: 0;
      width: 100%;
      height: 100%;
      overflow: hidden;
    }}
  </style>
</head>
<body>
  <div id=\"map\"></div>
  <script>
    const lat = {latitude};
    const lng = {longitude};
    const locationName = {safe_name};

    const map = L.map('map').setView([lat, lng], 13);

    L.tileLayer('https://{{s}}.tile.openstreetmap.org/{{z}}/{{x}}/{{y}}.png', {{
      maxZoom: 19,
      attribution: '&copy; OpenStreetMap contributors'
    }}).addTo(map);

    const marker = L.marker([lat, lng]).addTo(map);
    marker.bindPopup(locationName).openPopup();

    map.setView([lat, lng], 13);
  </script>
</body>
</html>
"""


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Waste Records")
        self.resize(1100, 500)

        self.map_window = None

        central = QWidget(self)
        self.setCentralWidget(central)

        layout = QVBoxLayout(central)
        top_row = QHBoxLayout()
        layout.addLayout(top_row)

        self.view_on_map_btn = QPushButton("View on Map")
        self.view_on_map_btn.clicked.connect(self.on_view_on_map_clicked)
        top_row.addStretch(1)
        top_row.addWidget(self.view_on_map_btn)

        self.table = QTableWidget(self)
        self.table.setColumnCount(8)
        self.table.setHorizontalHeaderLabels(
            [
                "ID",
                "Waste Type",
                "Category",
                "Quantity",
                "Weight (kg)",
                "Collection Date",
                "Location",
                "Status",
            ]
        )
        self.table.setSelectionBehavior(QTableWidget.SelectRows)
        self.table.setSelectionMode(QTableWidget.SingleSelection)
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table.horizontalHeader().setStretchLastSection(True)
        self.table.horizontalHeader().setDefaultAlignment(Qt.AlignLeft)

        layout.addWidget(self.table)

        self.populate_demo_data()

    def populate_demo_data(self):
        rows = [
            ["8", "Plastic", "Medical", "3", "3", "2026-03-01", "tunis", "Disposed"],
            ["9", "Glass", "Household", "2", "2", "2026-03-01", "ariana", "Collected"],
            ["10", "Metal", "Industrial", "4", "5", "2026-02-28", "nabeul", "In Transit"],
            ["11", "Organic", "Household", "1", "1", "2026-03-01", "sousse", "Pending"],
        ]

        self.table.setRowCount(len(rows))
        for r, row_data in enumerate(rows):
            for c, value in enumerate(row_data):
                self.table.setItem(r, c, QTableWidgetItem(value))

    def on_view_on_map_clicked(self):
        selected_ranges = self.table.selectedRanges()
        if not selected_ranges:
            QMessageBox.warning(self, "No selection", "Please select a row first.")
            return

        selected_row = selected_ranges[0].topRow()

        location_item = self.table.item(selected_row, 6)
        location_name = location_item.text().strip() if location_item else ""

        if not location_name:
            QMessageBox.warning(self, "Missing location", "Selected row has no location value.")
            return

        coords = CITY_COORDS.get(location_name.lower())
        if coords is None:
            QMessageBox.warning(
                self,
                "Unknown city",
                f"No coordinates found for location: {location_name}\n"
                f"Add it to CITY_COORDS dictionary.",
            )
            return

        latitude, longitude = coords

        self.map_window = MapWindow(location_name, latitude, longitude, self)
        self.map_window.show()
        self.map_window.raise_()
        self.map_window.activateWindow()


def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
