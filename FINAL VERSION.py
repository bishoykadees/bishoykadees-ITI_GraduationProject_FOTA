# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'PC.ui'
##
## Created by: Qt User Interface Compiler version 5.14.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

import sys
import socket
from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *

records = []
#create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
success = 0

class Ui_Form(object):
    def setupUi(self, Form):
        if Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(510, 325)
        self.textEdit = QTextEdit(Form)
        self.textEdit.setObjectName(u"textEdit")
        self.textEdit.setEnabled(True)
        self.textEdit.setGeometry(QRect(10, 110, 491, 211))
        self.textEdit.setReadOnly(True)
        self.connectToServer_Button = QPushButton(Form)
        self.connectToServer_Button.setObjectName(u"connectToServer_Button")
        self.connectToServer_Button.setGeometry(QRect(50, 40, 111, 31))
        self.browse_Button = QPushButton(Form)
        self.browse_Button.setObjectName(u"browse_Button")
        self.browse_Button.setGeometry(QRect(200, 40, 111, 31))
        self.sendFile_Button = QPushButton(Form)
        self.sendFile_Button.setObjectName(u"sendFile_Button")
        self.sendFile_Button.setGeometry(QRect(350, 40, 111, 31))

        self.connectToServer_Button.clicked.connect(self.connectToServer_Func)
        self.browse_Button.clicked.connect(self.browse_Func)
        self.sendFile_Button.clicked.connect(self.send_func)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"FoTa", None))
        self.connectToServer_Button.setText(QCoreApplication.translate("Form", u"Connect to server", None))
        self.browse_Button.setText(QCoreApplication.translate("Form", u"Browse", None))
        self.sendFile_Button.setText(QCoreApplication.translate("Form", u"Send", None))
    # retranslateUi

    def connectToServer_Func(self):
      global sock
      sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      #connect the socket to the port where the server is listening
      server_address = ('192.168.100.1',333)
      #print(str(sys.stderr)+'\n')
      #print('connecting to '+ str(server_address) +'\n')
      try:
        sock.connect(server_address)
        self.textEdit.append("Connected to server successfully!")
      except socket.error as er:
        print("Failed to connect to server!")
        self.textEdit.append("Failed to connect to server!")
        self.textEdit.append("Please try again!")

    def browse_Func(self):
      dlg = QFileDialog(filter = 'Hex-Files (*.hex)')
      dlg.setFileMode(QFileDialog.AnyFile)
      #dlg.setFilter("(*.hex)")
      #filenames = QStringList()

      if dlg.exec_() == QFileDialog.Accepted:
        global records
        #get file path
        dest_file = dlg.selectedFiles()[0]
        hex_file = open(dest_file,'r')
        records = hex_file.readlines()
        hex_file.close()
        self.textEdit.append('File opened!')
        #for r in records:
        #print(records)
      else:
        self.textEdit.append('Failed to open the file')

    def send_func(self):
      #print(records)
      global success
      try:
        sock.sendall(bytes('ITI','ascii'))
        counter = 1
        print('sending ITI')
        data = sock.recv(3)
        print('recieved ' + data.decode('ascii') + '\n')
        str_data = data.decode('ascii')
        if str_data != 'YES':
          print('Not yes')
          return
      except socket.error as er:
        print('Failed to handshake')
      for r in records:
        #print(r)
        try:
          sock.sendall(bytes(r,'ascii'))
          print('sending '+ r + '\n')
          if r != records[-1]:
            data = sock.recv(3)
            print('recieved ' + data.decode('ascii') + '\n')
            str_data = data.decode('ascii')
            if str_data == 'YES':
              print('recieved '+str_data + '\n')
            else:
              break
          success = 1
        except socket.error as er:
          success = 0
      #error
      print('closing socket\n')
      sock.close()
      if success == 1:
        self.textEdit.append('File is send to target successfully!')
      elif success == 0:
        self.textEdit.append('Connection failed')

app = QApplication(sys.argv)
Widget = QWidget()
Widget = QWidget()
Form = Ui_Form()
Form.setupUi(Widget)
Widget.show()
sys.exit(app.exec_())