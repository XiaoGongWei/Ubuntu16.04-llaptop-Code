from PyQt5.QtWidgets import (QWidget, QPushButton, QMessageBox, QDesktopWidget, \
                             QHBoxLayout, QVBoxLayout, QLabel)
from PyQt5.QtGui import QIcon, QFont



class MyWindow(QWidget):

    def __init__(self):
        super().__init__()
        self.initWindow()

    def initWindow(self):
        self.resize(500, 300)
        deskcenter = QDesktopWidget().availableGeometry().center()
        deskcenter.setX(deskcenter.x() - 300)
        deskcenter.setY(deskcenter.y() - 200)
        self.move(deskcenter)
        self.setWindowIcon(QIcon('baidu.ico'))


        btn = QPushButton()
        btn.resize(100, 30)
        btn.setToolTip("this is <b>XGW</b>.")
        btn.setText("Click Here")
        btn.clicked.connect(self.close)

        btn2 = QPushButton()
        btn2.resize(120, 30)
        btn2.setText("QMessageBox")
        btn2.clicked.connect(self.but2connect)

        lab1 = QLabel()
        qfont = QFont()
        qfont.setPixelSize(22)
        qfont.setBold(True)
        qfont.setItalic(True)
        lab1.setFont(qfont)
        lab1.setText("i'm a QLabel")

        hlayout = QHBoxLayout()
        hlayout.addWidget(btn)
        hlayout.addWidget(btn2)

        hlayout1 = QHBoxLayout()
        hlayout1.addWidget(lab1)

        vlayout = QVBoxLayout()
        vlayout.addLayout(hlayout)
        vlayout.addLayout(hlayout1)


        self.setLayout(vlayout)
        self.setStatusTip("xiaogongwei")
        self.setWindowTitle("PyQt5")
        self.setToolTip("this is ToolTip")
        self.show()

    def closeEvent(self, QCloseEvent):
        reply = QMessageBox.question(self, "Close", "Are you Quit?", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            QCloseEvent.accept()

        else:
            QCloseEvent.ignore()

    def but2connect(self):
        reply = QMessageBox.question(self, "Message", "Are you David?", QMessageBox.Yes|
                                QMessageBox.No, QMessageBox.Yes)
        if reply == QMessageBox.Yes:
            newMsg = QMessageBox(self)
            newMsg.setWindowTitle("Welcome")
            newMsg.setText("Welcome adminstor: David.")
            newMsg.show()
        else:
            QMessageBox.warning(self, "Warning", "You are spy.", QMessageBox.No, QMessageBox.No)
