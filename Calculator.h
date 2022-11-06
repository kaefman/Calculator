/*!
 \file
 \brief Заголовочный файл с описанием классов

 Данный файл содержит в себе определения основных 
 классов, используемых в программе
*/
 #pragma once
 
 #include <QWidget>
 #include <QStack>
 
 class QLCDNumber;
 class QPushButton;
 
 /*!
 \brief Основной класс калькулятора
 */
 class Calculator : public QWidget {
     Q_OBJECT
 private:
     QLCDNumber*     m_plcd;        // Поле используется для хранения текущего результата операции
     QStack<QString> m_stk;         // Стек, в котором хранится текцщее вычисление
     QString         m_strDisplay;  // Строка, выводимая в данный момент на дисплей
 
 public:
     Calculator(QWidget* pwgt = 0);
 
     QPushButton* createButton(const QString& str);
     void         calculate   (                  );
 
 public slots:
     void slotButtonClicked();
 };
 
