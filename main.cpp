#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWidgets>
#include <QPixmap>
#include <QPixmap>
#include <QPoint>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;
template <typename T>
class smart_ptr {
    T * obj;
public:
    smart_ptr(){}
    smart_ptr(T *obj)
        : obj(obj){ }
    ~smart_ptr() {
        delete obj;
    }
    T* operator->() { return obj; }
    T& operator* () { return *obj; }
};
class PlagiarismChecker : public QWidget
{
public:
    PlagiarismChecker(QWidget *parent = nullptr)
        : QWidget(parent){
        setWindowTitle("Plagiarism Checker");
        this->textEdit = new QTextEdit("",this);
        this->textEdit->setFixedSize(250, 250);
        this->checkButton = new QPushButton("Change Color", this);
        this->checkButton->setFixedSize(250, 50);
        this->checkButton->move(0, 250);
        this->labelResult = new QLabel("-%", this);
        this->labelResult->setFixedSize(250, 300);
        this->labelResult->move(250, 0);
        this->labelResult->setAlignment(Qt::AlignCenter);
        this->labelResult->setFont(QFont("Times", 20));
        connect(checkButton, &QPushButton::clicked, this,
                &PlagiarismChecker::actionCheckPlagiarism);
        this->spinBox = *(new smart_ptr<QSpinBox>(new QSpinBox(this)));
        this->spinBox->setMinimum(2);
        this->spinBox->setMaximum(10);
        this->spinBox->displayIntegerBase();
        this->spinBox->valueChanged(3);
        this->spinBox->move(250, 0);
    }
protected:
    QLabel *labelResult;
    QPushButton *checkButton;
    QTextEdit *textEdit;
    smart_ptr<QSpinBox> spinBox;
protected slots:
    void actionCheckPlagiarism(){
        QString textQS = this->textEdit->toPlainText();
        string textS = textQS.toStdString();
        int k = this->spinBox->value();
        if(textS.size()==0){
            return;
        }
        double resultD = PlagiarismChecker::calculatePlagiarism(textS,
                                                                k) * 100.0;
        ostringstream sstream;
        sstream << resultD;
        string resultS = sstream.str();
        resultS.push_back('%');
        QString resultQS = QString::fromStdString(resultS);
        this->labelResult->setText(resultQS);
    }
private:
    // Function to generate shingles from a given text
    static unordered_set<string> generateShingles(const string& text,
                                                  int k) {
        unordered_set<string> shingles;
        for (int i = 0; i < text.length() - k + 1; ++i) {
            shingles.insert(text.substr(i, k));
        }
        return shingles;
    }
    // Function to check plagiarism using Shingling algorithm
    static double calculatePlagiarism(const string& inputText, int k) {
        string filePath = "D://oop10lab//Text.txt";
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << filePath << endl;
            return -1.0; // Error code indicating failure
        }
        string fileText((istreambuf_iterator<char>(file)),
                        istreambuf_iterator<char>());
        file.close();
        unordered_set<string> inputShingles =
            PlagiarismChecker::generateShingles(inputText, k);
        unordered_set<string> fileShingles =
            PlagiarismChecker::generateShingles(fileText, k);
        int commonShingles = 0;
        for (const string& shingle : inputShingles) {
            if (fileShingles.find(shingle) != fileShingles.end()) {
                ++commonShingles;
            }
        }
        return (2.0 * commonShingles) / (inputShingles.size() +
                                         fileShingles.size());
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "untitled1_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    PlagiarismChecker plagiarismChecker;
    plagiarismChecker.setFixedSize(500, 300);
    plagiarismChecker.show();
    return a.exec();
}
