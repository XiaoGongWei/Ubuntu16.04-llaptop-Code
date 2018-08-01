from PyQt5.QtWidgets import QApplication
from QtWindows import MyWindow
import sys



if __name__ == "__main__":
    app = QApplication(sys.argv)
    wnd = MyWindow()
    sys.exit(app.exec_())