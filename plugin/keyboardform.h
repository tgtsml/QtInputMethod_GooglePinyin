#ifndef KEYBOARDFORM_H
#define KEYBOARDFORM_H

#include <QWidget>
class QPushButton;
class QLabel;

class KeyboardForm : public QWidget
{
    Q_OBJECT

public:
    KeyboardForm(QWidget *parent = 0);
    void clearChineseCache();

private:
    void chineseCharactersUpdatePrevious();
    void chineseCharactersUpdateNext();
    void chineseCharactersSelected();
    void btnBackspaceClicked();
    void btnEnterClicked();
    void btnUpperClicked();
    void btnSymbolsClicked();
    void btnLanguageClicked();
    void btnBlankspaceClicked();
    void btnEmojiClicked();
    void characterButtonClicked();
    void updateKeyboard();
    void updateButtonStateOfChineseCharacters();
    void searchChineseCharacters(const int &currentpage);
    void hideKeyboard();

    QList<QPushButton*> character_btns_list, chinese_characters_list, change_chinese_characters_page_list;
    enum InputMode{zh, en, symb};
    InputMode current_mode, last_mode;
    QWidget *widget_keyboard, *widget_pinyin;
    bool upper_mode;
    QLabel *m_label_pinyin;
    int m_symbol_page;

signals:
    void sendKeyToFocusItem(const QString &keytext);
};

#endif // KEYBOARDFORM_H
