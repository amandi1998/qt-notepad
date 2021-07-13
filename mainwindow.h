#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Provides the main application window on which the user interface
// is built by adding widgets
#include <QMainWindow>

// Use the standard UI namespace which is tied to the .ui file
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
       // Declares our class as a QObject which is the base class
       // for all Qt objects
       // QObjects handle events
       // Each QObject executes on a thread
    Q_OBJECT


public:
        // Declare a constructor and by passing 0 we state this widget
       // has no parent
    MainWindow(QWidget *parent = nullptr);

      // Declare a destructor which will free resources
    ~MainWindow();

private slots:
    void on_actionNew_Ctrl_N_triggered();

    void on_actionOpen_Ctrl_O_triggered();

    void on_actionSave_Ctrl_S_triggered();

    void on_actionSave_as_Ctrl_Shift_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_Ctrl_C_triggered();

    void on_action_Paste_Ctrl_V_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_Ctrl_Z_triggered();

    void on_actionAboutt_Notepad_triggered();

    void on_actionPrint_Ctrl_P_triggered();

    void on_actionExit_triggered();

    void on_actionFont_triggered();

    void on_actionColour_triggered();

    void on_actionBackground_Colour_triggered();

    void on_actionBacground_Colour_Edit_Text_triggered();

private:
    // Point to the ui class
    Ui::MainWindow *ui;

    // A Qt character string that will hold text entered by the user
    QString file_path_;                                               /* declaring a string variable which name is file_path.
                                                                      This "file_path" is used to saved the path of the file location.*/
};
#endif // MAINWINDOW_H
