#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QAction>
#include <string>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // <============== this creates an action group which enables the
    // user to see which option is choosed from the dropdown menu ================ >

    QActionGroup * alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(ui->actionMale);
    alignmentGroup->addAction(ui->actionFemale);
    ui->actionFemale->setChecked(true);


    // <========== SIGNALS AND SLOTS ====================================================>

   // <=========== Height and weight's spin box and slider are connected using the automatic way ============>

    // updating the BMI value when weight slider is changed
    connect(ui->weight_slider,SIGNAL(valueChanged(int)),
                            this,SLOT(calculate_bodymassindex()));

    // updating the BMI value when height slider is changed
    connect(ui->height_slider,SIGNAL(valueChanged(int)),
                            this,SLOT(calculate_bodymassindex()));

    // call the function reset when the reset button is pressed
    connect(ui->actionReset,SIGNAL(triggered(bool)),
                            this,SLOT(reset_values()));

    // quit the program when the quit button is pressed
    connect(ui->actionQuit,SIGNAL(triggered(bool)),
                            this,SLOT(close()));

    // Gender label is updated to male when clicked on the male option
    //in the dropdown menu
    connect(ui->actionMale,SIGNAL(triggered(bool)),
                            this,SLOT(update_gender_male()));

    // Gender label is updated to female when clicked on the female option
    //in the dropdown menu
    connect(ui->actionFemale,SIGNAL(triggered(bool)),
                            this,SLOT(update_gender_female()));

    // Whenver weight slider is changed, BMI interpretation is
    // updated by calling the interpretation function
    connect(ui->weight_slider,SIGNAL(valueChanged(int)),
                            this,SLOT(update_interpretation()));

    // Whenver weight slider is changed, BMI interpretation is
    // updated by calling the interpretation function
    connect(ui->height_slider,SIGNAL(valueChanged(int)),
                            this,SLOT(update_interpretation()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

// <====== this function updates the value of BMI on the lcd display ======== >
void MainWindow::calculate_bodymassindex(){

    // Receiving the values from the spinbox of weight and height
    // from their respective widgets
    int weight = ui->weight_spinbox->value();
    double height = (ui->height_spinbox->value()) * 0.01;


    // Calculating BMI using the variables weight and height
    double BMI = weight / (height * height);


    // checking if either of the height or weight is
    // equal to zero, if it is then the BMI should be zero
    if(height != 0 and weight != 0){
        ui->bodymassindex_label->setText(QString::number(BMI));
    }else{
        ui->bodymassindex_label->setText("-");
    }
}

// <========this function resets the values to 0 of height, weight
// bmi and interpretation ================================== >
void MainWindow::reset_values(){
    ui->weight_spinbox->setValue(0);
    ui->height_spinbox->setValue(0);
    ui->interpretation_label->setText("-");
    update_gender_female();
}

// <======== this functions updates the gender label
// to male ==============>
void MainWindow::update_gender_male(){

    QString male = QString::fromStdString("Male");
    ui->gender_label->setText(male);

}

// <======== this functions updates the gender label
// to female ==============>
void MainWindow::update_gender_female(){

    QString female = QString::fromStdString("Female");
    ui->gender_label->setText(female);
}

// <========= this function updates the interpretation
// description about the calculated BMI =================>
void MainWindow::update_interpretation(){

    int current_value = (ui->bodymassindex_label->text()).toDouble(); // getting the BMI value and converting to int

    QString current_gender = ui->gender_label->text();
    QString male = QString::fromStdString("Male");

    // to see if the interpreation should dislay nothin or not
    int weight = ui->weight_spinbox->value();
    double height = (ui->height_spinbox->value()) * 0.01;


    // the real part where BMI is compared and interpretation
    // is updated accordingly
    if(weight == 0 or height == 0){
        ui->interpretation_label->setText("-");
    } else if (current_gender == male){ // if the gender is male the
                                        //interpretation would be accordingly
        if (current_value <= 20.7){
            ui->interpretation_label->setText("Underweight");
        }
        else if (current_value > 20.7 and current_value <= 26.4){
            ui->interpretation_label->setText("Normal");
        }
        else if (current_value > 26.4 and current_value <= 27.8){
            ui->interpretation_label->setText("Slight overweight");
        }
        else if (current_value > 27.8 and current_value <= 31.1){
            ui->interpretation_label->setText("Overweight");
        }
        else if (current_value > 31.1){
            ui->interpretation_label->setText("Much overweight");
        }
    } else { // if the gender is female
            // the interpretation would be accordingly
        if (current_value <= 19.1){
            ui->interpretation_label->setText("Underweight");
        }
        else if (current_value > 19.1 and current_value <= 25.8){
            ui->interpretation_label->setText("Normal");
        }
        else if (current_value > 25.8 and current_value <= 27.3){
            ui->interpretation_label->setText("Slight overweight");
        }
        else if (current_value > 27.3 and current_value <= 32.2){
            ui->interpretation_label->setText("Overwight");
        }
        else if (current_value > 32.2){
            ui->interpretation_label->setText("Much overweight");
        }
    }
}

