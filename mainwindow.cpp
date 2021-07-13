#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>            // Adding QFile header file
#include <QFileDialog>     // Adding QFileDialog
#include <QTextStream>    // Adding  QTextStream header file
#include <QMessageBox>   // Adding QMessageBox header file
#include <QFontDialog>   // Adding QFontDialog header file
#include <QFont>        // Adding QFont header file
#include <QColorDialog>//Adding  QColorDialog header file
#include <QColor>     // Adding  QColor
#include <QPrinter>
#include <QPrintDialog>

// The Notepad constructor
MainWindow::MainWindow(QWidget *parent)

     // Call the QMainWindow constructor
    : QMainWindow(parent)

    // Create the UI class and assign it to the ui member
    , ui(new Ui::MainWindow)
{
    // Setup the UI
    ui->setupUi(this);

    // Have the textedit widget take up the whole window
    this->setCentralWidget(ui->textEdit);             /*To centralized the main widget*/

}

// Destructor that deletes the UI
MainWindow::~MainWindow()
{
    delete ui;
}

   // --------ADDING ICONS TO TOOLBAR & MENU -----



void MainWindow::on_actionNew_Ctrl_N_triggered()
{
      //To create file path
    file_path_="";        /*In here I called the file_path_ variable which I created before in mainwindow.h.
                            file_path_ variable is setted as empty string. Whenever somebody clicks New Button then,
                           "file_path_" will be resetted.*/


    // Clear the textEdit widget buffer
    ui->textEdit->setText("");   /*In here, basically doing ressetting of text editor using
                                   the global variable which is the "file_path_" */

}


      //-------- To open a file -------

void MainWindow::on_actionOpen_Ctrl_O_triggered()
{
    // Opens a dialog that allows you to select a file to open
    QString file_name_ = QFileDialog::getOpenFileName(this,"Open the file");

                      /*Declared a QString name as "file_name_" which is used for QFileDialog.
                        And called a stasic method - getOpenFileName.
                         getOpenFileName was provided two values as "this" and "caption:Open the file" */


    // An object for reading and writing files
    QFile file(file_name_);                  /*ceating an object as "file" and passed it to "file_name" from QFileDialog */

    // Store the currentFile name
    file_path_ =file_name_;              /*Then it will be saved globally.*/



    // Try to open the file as a read only file if possible or display a
        // warning dialog box
    if(!file.open(QFile::ReadOnly | QFile::Text)){         /* the if  condition is used to check whether
                                                              the file is open or not. If the file is  not opened,
                                                              it gives user to warning like "File is not open" */

       QMessageBox::warning(this,"..","File is not open.");
       return;                   /* Return - the reason for that, If the file is not opened.
                                    Then user does not want to work. Because this function is  based on void.
                                    So that from here (return) the program will no go further.  */
    }


    // Interface for reading text
    QTextStream in(&file);         /*When file is opened, need to perform tasks. Therefore, created QTextStream then,
                                     gave "variable name: in" and "references:&file".*/

   // Copy text in the string
    QString text =in.readAll();    /* Created "QString" and named it as "text". And whatever is there in the stream
                                      it will passed to string - in.readAll().  */

     // Put the text in the textEdit widget
    ui->textEdit->setText(text);            /* Onced it has string, Then it is setted  to this  textEdit as setText(text)*/

    // To close the file
    file.close();
}

      // --------- To Save --------

void MainWindow::on_actionSave_Ctrl_S_triggered()
{

    // QString file_name_ = QFileDialog::getSaveFileName(this,"Open the file");
       QFile file( file_path_); /*In here directely provided the path of the file which user wants to save.
                                  * Beacuse it is already opened.*/
        if(!file.open(QFile::WriteOnly | QFile::Text)){
             QMessageBox::warning(this,"..","File is not open.");
              return;
        }
      QTextStream out(&file);
      QString text = ui->textEdit->toPlainText(); /* In here to get text from textEdit */
      out << text;  /* Here take "out" variable and passed "text"  to this variable */
      file.flush(); /*Flush the  file */
      file.close(); /*To close the file*/
}



    // ------------- Save as ----------------

void MainWindow::on_actionSave_as_Ctrl_Shift_triggered()
{
         // Opens a dialog for saving a file
    QString file_name_ = QFileDialog::getSaveFileName(this,"Open the file");

     // An object for reading and writing files
     QFile file(file_name_);

      // Store the currentFile name
     file_path_ = file_name_;

     // Try to open a file with write only options
      if(!file.open(QFile::WriteOnly | QFile::Text)){
           QMessageBox::warning(this,"..","File is not saved.");
            return;
      }

      // Interface for writing text
    QTextStream out(&file);

    // Copy text in the textEdit widget and convert to plain text
    QString text = ui->textEdit->toPlainText();

     // Output to file
    out << text;

    //To Flush the  file
    file.flush();

     //To close the file
    file.close();

}


    // ------ To cut ------
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


      //--------- To Copy --------

void MainWindow::on_actionCopy_Ctrl_C_triggered()
{
   ui->textEdit->copy(); /* ui->textEdit->copy(); and just call copy function*/
}


   //-------- To Paste ----------


void MainWindow::on_action_Paste_Ctrl_V_triggered()
{
    ui->textEdit->paste();
}



        //----- Redo -----------------

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
    //--------- Undo ---------------
void MainWindow::on_actionUndo_Ctrl_Z_triggered()
{
    ui->textEdit->undo();
}


 // ------------ About -------------

void MainWindow::on_actionAboutt_Notepad_triggered()
{
    QString about_text;  /*Users will be able to know the About the " EasyNotes - Notepad by using about button"*/
    about_text  = "Auther : Amandi Soysa \n ";
    about_text += "Date : 21/12/2020 \n";
    about_text += "(C) Q-Notepad (R) \n";
    about_text += "This Q-Notepad is created by\n using Qt framework with C++.\n ";

    QMessageBox::about(this,"About Q-Notepad",about_text);
}

   // ------ To Print ---------

void MainWindow::on_actionPrint_Ctrl_P_triggered()
{
       // Allows for interacting with printer
        QPrinter printer;                             /*Declaring object as QPrinter and named it as printer */

      // put printer name here
      printer.setPrinterName("Amandi's printer");     /*Set the printer name as Amandi's printer*/

      // Create the print dialog and pass the name and parent
      QPrintDialog dialog(&printer,this);

        if(dialog.exec() ==QDialog::Rejected)    /* Using if condition, check wheather,
                                                  user selected printer is correct or not correct */

        return;     /*If the printer rejected, It will be return. Because function is void type.*/


       // Send the text to the printer
      ui->textEdit->print(&printer);    /*Otherwise, user can use the text, which is in their "textEditor",
                                          and print. And passed the refereence value "printer"*/


}

void MainWindow::on_actionExit_triggered()
{       // To exit
     QCoreApplication::quit(); /*using exit method can be closed the EasyNotes - Notepad*/
}

void MainWindow::on_actionFont_triggered()
{           // To change font

    bool ok;                     /*Added bool for check wheather any Font is selcted or not.
                                  Therefore, declare a variable for "bool ok"*/

    QFont font = QFontDialog::getFont(&ok,this); /*Creating QFont object, it named as "font".
                                                    And used "QFontDialog" and static method "getFont()"
                                                    for assign the booling refereance "&ok" which i created before. */

        if(ok){                           /* If the font is selected, Need to provide font widget.
                                            " ui->textEdit->setFont(font);" */
       ui->textEdit->setFont(font);
    } else return;                       /* Otherwise it  return. Because function type is void.*/

}

void MainWindow::on_actionColour_triggered()
{        //To change the text colour
  QColor color = QColorDialog::getColor(Qt::white,this,"Choose colour");
         /*To change the text colour. using the
         user can change any clour what they want. Created QColor object named as "color".
         And used QColorDialogQColorDialog and static method "getColor()"
         for assigned default "Qt::white" colour.  */

  if(color.isValid()){     /* In here,  the colour is check whaether is it valied or
                              not valid using the if condition.*/

      ui->textEdit->setTextColor(color);  /*In here, colour is setted for text */

  }
}

void MainWindow::on_actionBackground_Colour_triggered()
{               // To change Background colour
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose colour");
        if(color.isValid()){
            ui->textEdit->setPalette(QPalette(color));  /*easy note- notepad Background colour will be changed.*/
     }
}

void MainWindow::on_actionBacground_Colour_Edit_Text_triggered()
{              //To change text backgroung colour
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose colour");
    if(color.isValid()){
         ui->textEdit->setTextBackgroundColor(color); /*Only text background colour will be changed - Only black colour works for background colour*/
  }

}
