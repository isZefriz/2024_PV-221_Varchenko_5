#include "qboxlayout.h"
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>

// Функция для проверки на плагиат
bool checkPlagiarism(QString text1, QString text2) {
    // Здесь можно реализовать алгоритм проверки на плагиат, например, сравнивая слова в текстах
    // Возвращаем true, если тексты считаются плагиатом, и false в противном случае
    if (text1 == text2) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создаем текстовые поля для ввода текста
    QTextEdit *textEdit1 = new QTextEdit();
    QTextEdit *textEdit2 = new QTextEdit();

    // Создаем кнопку для запуска проверки на плагиат
    QPushButton *checkButton = new QPushButton("Check Plagiarism");

    // Соединяем сигнал нажатия на кнопку с обработчиком
    QObject::connect(checkButton, &QPushButton::clicked, [&]() {
        if (checkPlagiarism(textEdit1->toPlainText(), textEdit2->toPlainText())) {
            QMessageBox::information(nullptr, "Plagiarism Check", "Texts are plagiarised!");
        } else {
            QMessageBox::information(nullptr, "Plagiarism Check", "Texts are not plagiarised.");
        }
    });

    // Создаем графическое окно приложения
    QWidget window;
    QVBoxLayout layout(&window);
    layout.addWidget(textEdit1);
    layout.addWidget(textEdit2);
    layout.addWidget(checkButton);

    window.show();

    return app.exec();
}
