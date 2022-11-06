// ======================================================================
 //  Calculator.cpp
 // ======================================================================
 //                   This file is a part of the book 
 //             "Qt 5.10 Professional programming with C++"
 //                       http://qt-book.com
 // ======================================================================
 //  Copyright (c) 2017 by Max Schlee
 // ======================================================================
 /*!
 \file
 \brief Файл с описанием методов класса Calculator

 Данный файл содержит в себе описания методов класса, 
 используемых в программе
*/

 #include <QtWidgets>
 #include "Calculator.h"
 
 // ----------------------------------------------------------------------
 /*!
 \brief Конструктор калькулятора

 Метод создает класс калькулятор, выделяет память для всех полей.
 */
 Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
 {
     m_plcd = new QLCDNumber(12);
     m_plcd->setSegmentStyle(QLCDNumber::Flat);
     m_plcd->setMinimumSize(150, 50);
 
     QChar aButtons[4][4] = {{'7', '8', '9', '/'},
                             {'4', '5', '6', '*'},
                             {'1', '2', '3', '-'},
                             {'0', '.', '=', '+'}
                            };
 
     //Layout setup
     QGridLayout* ptopLayout = new QGridLayout;
     ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);    
     ptopLayout->addWidget(createButton("CE"), 1, 3);
 
     for (int i = 0; i < 4; ++i) {
         for (int j = 0; j < 4; ++j) {
            ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
         }
     }
     setLayout(ptopLayout);
 }
 
 // ----------------------------------------------------------------------
 /*!
 \brief Метод создания кнопок

 Метод используется при создании всех кнопок в процессе
 работы конструктора.
 
 \param str Текст, расположенный на кнопке
 */
 QPushButton* Calculator::createButton(const QString& str)
 {
     QPushButton* pcmd = new QPushButton(str);
     pcmd->setMinimumSize(40, 40);
     connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
     return pcmd;
 }
 
 
 // ----------------------------------------------------------------------
 /*!
 \brief Метод, подсчитывающий результат операциии

 Метод определяет производимые подсчеты и выводит результат.
 Вызывается при выполнении какой-либо операции.
 */
 void Calculator::calculate()
 {
     qreal   fOperand2    = m_stk.pop().toFloat();
     QString strOperation = m_stk.pop();
     qreal   fOperand1    = m_stk.pop().toFloat();
     qreal   fResult      = 0;
 
     if (strOperation == "+") {
         fResult = fOperand1 + fOperand2;
     }
     if (strOperation == "-") {
         fResult = fOperand1 - fOperand2;
     }
     if (strOperation == "/") {
         fResult = fOperand1 / fOperand2;
     }
     if (strOperation == "*") {
         fResult = fOperand1 * fOperand2;
     }
     m_plcd->display(fResult);
 }
 
 // ----------------------------------------------------------------------
 /*!
 \brief Метод нажатия на кнопки

 Метод обрабатывает каждое нажатие и в зависимости от того, 
 какое действие выполняет пользователь, производит вычисления,
 обрабатывает и добавляет элементы в стек или очищает стек.
 */
 void Calculator::slotButtonClicked()
 {
     QString str = ((QPushButton*)sender())->text();
 
     if (str == "CE") {
         m_stk.clear();
         m_strDisplay = "";
         m_plcd->display("0");
         return;
     }
     if (str.contains(QRegExp("[0-9]"))) {
         m_strDisplay += str;
         m_plcd->display(m_strDisplay.toDouble());
     }
     else if (str == ".") {
         m_strDisplay += str;
         m_plcd->display(m_strDisplay);
     }
     else {
         if (m_stk.count() >= 2) {
             m_stk.push(QString().setNum(m_plcd->value()));
             calculate();
             m_stk.clear();
             m_stk.push(QString().setNum(m_plcd->value()));
             if (str != "=") {
                 m_stk.push(str);
             }
         }
         else {
             m_stk.push(QString().setNum(m_plcd->value()));
             m_stk.push(str);
             m_strDisplay = "";
         }
     }
 }
