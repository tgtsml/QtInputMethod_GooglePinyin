#include "keyboardform.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QFile>
#include <QApplication>
#include "pinyinime.h"

using namespace ime_pinyin;

#define chinesecharacters_number    7
const char *keyboard_characters = "qwertyuiopasdfghjklzxcvbnm,.?";
const QString keyboard_symbols[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                                   "@", "#", "_", "\"", "“", "”", ",", "，", ".", "。",
                                   ";", "；", ":", "：", "'", "’", "、", "!", "！",
                                   "~", "～", "+", "-", "*", "/", "=", "÷", "×", "√",
                                   "`", "?", "^", "&&", "%", "|", "(", ")", "（", "）",
                                   "[", "]", "【", "】", "{", "}", "<", ">", "《",
                                   "》", "$", "€", "￡", "￠", "￥", "§", "—", "／", "＼",
                                   "·", "……", "——", "→", "←", "↑", "↓", "■", "□", "●",
                                   "○", "『", "』", "「", "」", "★", "☆", "◆", "◇"}; //29*3

KeyboardForm::KeyboardForm(QWidget *parent)
    : QWidget(parent)
{
    character_btns_list.clear();
    current_mode = InputMode::en;
    upper_mode = false;
    m_symbol_page = 0;

    this->setFixedSize(800,250);
    int keyboard_btn_width = this->width()/11.5;
    int keyboard_btn_height = this->height()/5.0;

    //设置主窗体样式
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Tool | \
                         Qt::FramelessWindowHint | \
                         Qt::WindowStaysOnTopHint | \
                         Qt::WindowDoesNotAcceptFocus);

    //加载QSS样式表
    QFile qss(":/res/stylesheet.qss");
    if(false == qss.open(QFile::ReadOnly))return;
    this->setStyleSheet(qss.readAll());
    qss.close();

    //图标字体
    int fontId = QFontDatabase::addApplicationFont(":/res/FontAwesome.otf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont btnicofont(fontName);
    btnicofont.setPixelSize(10);

    //单行布局
    QHBoxLayout *hb[6];
    for(int i=0; i<6; i++)
    {
        hb[i] = new QHBoxLayout();
        hb[i]->setMargin(0);
        i == 1 ? hb[i]->setSpacing(2) : hb[i]->setSpacing(0);
    }

    widget_pinyin = new QWidget(this);
    widget_pinyin->setFixedHeight(keyboard_btn_height);
    //拼音缓存
    m_label_pinyin = new QLabel(this);
    m_label_pinyin->setFixedHeight(keyboard_btn_height*0.4);
    hb[0]->addWidget(m_label_pinyin);
    hb[0]->addStretch(1);

    //汉子缓存
    for(int i=0; i<chinesecharacters_number; i++)
    {
        QPushButton *btn = new QPushButton(this);
        btn->setFixedHeight(keyboard_btn_height*0.6);
        hb[1]->addWidget(btn);
        if(i != chinesecharacters_number - 1) hb[1]->addStretch(1);
        if (i == 0 || i == chinesecharacters_number-1)
        {
            change_chinese_characters_page_list.append(btn);
            btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            btn->setFont(btnicofont);
            btn->setText(i == 0 ? QString(QChar(0xf0d9)) : QString(QChar(0xf0da)));
            btn->setObjectName("hanzichangepage");
            i == 0 ? \
            connect(btn, &QPushButton::clicked, this, &KeyboardForm::chineseCharactersUpdatePrevious) :
            connect(btn, &QPushButton::clicked, this, &KeyboardForm::chineseCharactersUpdateNext);
        }
        else
        {
            chinese_characters_list.append(btn);
            btn->setObjectName("hanzicandidates");
            connect(btn, &QPushButton::clicked, this, &KeyboardForm::chineseCharactersSelected);
        }
    }

    QVBoxLayout *vb_pinyin = new QVBoxLayout(widget_pinyin);
    vb_pinyin->addLayout(hb[0]);
    vb_pinyin->addLayout(hb[1]);
    vb_pinyin->setMargin(0);
    vb_pinyin->setSpacing(0);

    widget_keyboard = new QWidget(this);
    widget_keyboard->setFixedHeight(keyboard_btn_height*4.0);
    //键盘
    for(int i=0; i<29; i++)
    {
        QPushButton *btn = new QPushButton(QChar(keyboard_characters[i]),this);
        btn->setFixedSize(keyboard_btn_width, keyboard_btn_height);
        character_btns_list.append(btn);
        connect(btn, &QPushButton::clicked, this, &KeyboardForm::characterButtonClicked);
    }
    //第一排字母:0-9
    for(int i=0; i<10; i++)
    {
        hb[2]->addWidget(character_btns_list.at(i));
    }
    QPushButton *btn_backspace = new QPushButton(QChar(0xf060));
    btn_backspace->setFont(btnicofont);
    btn_backspace->setFixedSize(keyboard_btn_width*1.5, keyboard_btn_height);
    btn_backspace->setObjectName("function_button");
    hb[2]->addWidget(btn_backspace);
    connect(btn_backspace, &QPushButton::clicked, this, &KeyboardForm::btnBackspaceClicked);
    //第二排字母:10-18
    hb[3]->addStretch(1);
    for(int i=10; i<19; i++)
    {
        hb[3]->addWidget(character_btns_list.at(i));
    }
    QPushButton *btn_enter = new QPushButton("Enter");
    btn_enter->setFixedSize(keyboard_btn_width*1.5, keyboard_btn_height);
    btn_enter->setObjectName("function_button");
    hb[3]->addWidget(btn_enter);
    hb[3]->addStretch(1);
    connect(btn_enter, &QPushButton::clicked, this, &KeyboardForm::btnEnterClicked);
    //第三排字母:20-26
    QPushButton *btn_upper = new QPushButton(QChar(0xf062));
    btn_upper->setFixedSize(keyboard_btn_width*1.5, keyboard_btn_height);
    btn_upper->setFont(btnicofont);
    btn_upper->setObjectName("function_button");
    hb[4]->addWidget(btn_upper);
    connect(btn_upper, &QPushButton::clicked, this, &KeyboardForm::btnUpperClicked);
    for(int i=19; i<29; i++)
    {
        hb[4]->addWidget(character_btns_list.at(i));
    }
    character_btns_list.append(btn_upper);
    //第四排功能键
    QPushButton *btn_symbols = new QPushButton(".?123");
    btn_symbols->setFixedSize(keyboard_btn_width*1.5, keyboard_btn_height);
    btn_symbols->setObjectName("function_button");
    hb[5]->addWidget(btn_symbols);
    connect(btn_symbols, &QPushButton::clicked, this, &KeyboardForm::btnSymbolsClicked);
    QPushButton *btn_language = new QPushButton(QChar(0xf0ac));
    btn_language->setFixedSize(keyboard_btn_width, keyboard_btn_height);
    btn_language->setFont(btnicofont);
    btn_language->setObjectName("function_button");
    hb[5]->addWidget(btn_language);
    connect(btn_language, &QPushButton::clicked, this, &KeyboardForm::btnLanguageClicked);
    QPushButton *btn_blankspace = new QPushButton("English");
    btn_blankspace->setFixedHeight(keyboard_btn_height);
    hb[5]->addWidget(btn_blankspace);
    character_btns_list.append(btn_blankspace);
    connect(btn_blankspace, &QPushButton::clicked, this, &KeyboardForm::btnBlankspaceClicked);
    QPushButton *btn_emoji = new QPushButton(QChar(0xf118));
    btn_emoji->setFixedSize(keyboard_btn_width, keyboard_btn_height);
    btn_emoji->setFont(btnicofont);
    btn_emoji->setObjectName("emoji");
    hb[5]->addWidget(btn_emoji);
    connect(btn_emoji, &QPushButton::clicked, this, &KeyboardForm::btnEmojiClicked);
    QPushButton *btn_hidekeyboard = new QPushButton(QString(QChar(0xf11c)).append(QChar(0xf103)));
    btn_hidekeyboard->setFixedSize(keyboard_btn_width*1.5, keyboard_btn_height);
    btn_hidekeyboard->setFont(btnicofont);
    btn_hidekeyboard->setObjectName("function_button");
    hb[5]->addWidget(btn_hidekeyboard);
    connect(btn_hidekeyboard, &QPushButton::clicked, this, &KeyboardForm::hideKeyboard);

    QVBoxLayout *vb_keyboard = new QVBoxLayout(widget_keyboard);
    vb_keyboard->setMargin(0);
    vb_keyboard->setSpacing(0);
    for(int i=2; i<6; i++)
    {
        vb_keyboard->addLayout(hb[i]);
    }

    QVBoxLayout *vb_system = new QVBoxLayout(this);
    vb_system->setMargin(0);
    vb_system->setSpacing(0);
    vb_system->addStretch(1);
    vb_system->addWidget(widget_pinyin);
    vb_system->addWidget(widget_keyboard);
    widget_pinyin->hide();

    updateButtonStateOfChineseCharacters();
}

void KeyboardForm::updateButtonStateOfChineseCharacters()
{
    if(m_label_pinyin->text().isEmpty())
    {
        m_label_pinyin->setHidden(true);
        change_chinese_characters_page_list.at(0)->setHidden(true);
        change_chinese_characters_page_list.at(1)->setHidden(true);
    }
    else
    {
        m_label_pinyin->setHidden(false);
        change_chinese_characters_page_list.at(0)->setHidden(false);
        change_chinese_characters_page_list.at(1)->setHidden(false);
    }
}

void KeyboardForm::chineseCharactersUpdatePrevious()
{
    searchChineseCharacters(-1);
}

void KeyboardForm::chineseCharactersUpdateNext()
{
    searchChineseCharacters(1);
}

void KeyboardForm::chineseCharactersSelected()
{
    emit sendKeyToFocusItem(((QPushButton*)sender())->text());
    clearChineseCache();
}

void KeyboardForm::btnBackspaceClicked()
{
    if(current_mode != InputMode::zh || m_label_pinyin->text().isEmpty())
    {
        emit sendKeyToFocusItem("\x7F");
    }
    else
    {
        m_label_pinyin->setText(m_label_pinyin->text().left(m_label_pinyin->text().length()-1));
        if(m_label_pinyin->text().isEmpty())
        {
            clearChineseCache();
        }
        else
        {
            searchChineseCharacters(0);
        }
    }
}

void KeyboardForm::btnEnterClicked()
{
    if(current_mode != InputMode::zh || m_label_pinyin->text().isEmpty())
    {
        emit sendKeyToFocusItem("\n");
    }
    else
    {
        emit sendKeyToFocusItem(m_label_pinyin->text());
        clearChineseCache();
    }
}

void KeyboardForm::btnUpperClicked()
{
    if(current_mode == InputMode::en)
    {
        upper_mode = !upper_mode;
    }
    else if(current_mode == InputMode::zh)
    {
        if(!m_label_pinyin->text().isEmpty() && m_label_pinyin->text().right(1).compare("'"))
        {
            m_label_pinyin->setText(m_label_pinyin->text().append("'"));
        }
    }
    else
    {
        if(m_symbol_page == 0)
        {
            m_symbol_page = 1;
            character_btns_list.at(character_btns_list.length()-2)->setText("2/3");
        }
        else if(m_symbol_page == 1)
        {
            m_symbol_page = 2;
            character_btns_list.at(character_btns_list.length()-2)->setText("3/3");
        }
        else
        {
            m_symbol_page = 0;
            character_btns_list.at(character_btns_list.length()-2)->setText("1/3");
        }
    }
    updateKeyboard();
}

void KeyboardForm::btnSymbolsClicked()
{
    if(current_mode != InputMode::symb)
    {
        widget_pinyin->setHidden(true);
        if(current_mode == InputMode::en)
        {
            character_btns_list.at(character_btns_list.length()-1)->setText("Symbols");
        }
        else if(current_mode == InputMode::zh)
        {
            character_btns_list.at(character_btns_list.length()-1)->setText("符号");
        }
        ((QPushButton*)sender())->setText("abc");
        last_mode = current_mode;
        current_mode = InputMode::symb;
        character_btns_list.at(character_btns_list.length()-2)->setText("1/3");
    }
    else
    {
        ((QPushButton*)sender())->setText(".?123");
        current_mode = last_mode;
        m_symbol_page = 0;
    }
    upper_mode = false;
    updateKeyboard();
}

void KeyboardForm::btnLanguageClicked()
{
    upper_mode = false;
    if(current_mode == InputMode::zh)
    {
        current_mode = InputMode::en;
    }
    else if(current_mode == InputMode::en)
    {
        current_mode = InputMode::zh;
    }
    if(current_mode != InputMode::symb)
    {
        last_mode = current_mode;
        updateKeyboard();
    }
}

void KeyboardForm::clearChineseCache()
{
    m_label_pinyin->setText("");
    for(int i=0; i<chinese_characters_list.length(); i++)
    {
        chinese_characters_list.at(i)->setText("");
    }
    updateButtonStateOfChineseCharacters();
}

void KeyboardForm::hideKeyboard()
{
    clearChineseCache();
    this->hide();
}

void KeyboardForm::updateKeyboard()
{
    if(current_mode != InputMode::zh)
    {
        clearChineseCache();
    }
    if(current_mode == InputMode::symb)
    {
        character_btns_list.at(character_btns_list.length()-2)->setCheckable(false);
        for(int i=0; i<29; i++)
        {
            character_btns_list.at(i)->setText(keyboard_symbols[i + m_symbol_page*29]);
        }
    }
    else
    {
        if(true == upper_mode && current_mode == InputMode::en)
        {
            character_btns_list.at(character_btns_list.length()-2)->setCheckable(true);
            character_btns_list.at(character_btns_list.length()-2)->setChecked(true);
            for(int i=0; i<26; i++)
            {
                character_btns_list.at(i)->setText(QChar(keyboard_characters[i]).toUpper());
            }
        }
        else
        {
            for(int i=0; i<26; i++)
            {
                character_btns_list.at(i)->setText(QChar(keyboard_characters[i]));
            }
        }
        if(current_mode == InputMode::en)
        {
            widget_pinyin->setHidden(true);
            character_btns_list.at(character_btns_list.length()-5)->setText(",");
            character_btns_list.at(character_btns_list.length()-4)->setText(".");
            character_btns_list.at(character_btns_list.length()-3)->setText("?");
            character_btns_list.at(character_btns_list.length()-2)->setText(QChar(0xf062));
            character_btns_list.at(character_btns_list.length()-1)->setText("English");
        }
        else if(current_mode == InputMode::zh)
        {
            character_btns_list.at(character_btns_list.length()-2)->setCheckable(false);
            widget_pinyin->setHidden(false);
            character_btns_list.at(character_btns_list.length()-5)->setText("，");
            character_btns_list.at(character_btns_list.length()-4)->setText("。");
            character_btns_list.at(character_btns_list.length()-3)->setText("？");
            character_btns_list.at(character_btns_list.length()-2)->setText("分词");
            character_btns_list.at(character_btns_list.length()-1)->setText("拼音");
        }
    }
}

void KeyboardForm::btnBlankspaceClicked()
{
    if(current_mode != InputMode::zh || m_label_pinyin->text().isEmpty())
    {
        emit sendKeyToFocusItem(" ");
    }
    else
    {
        emit sendKeyToFocusItem(chinese_characters_list.at(0)->text());
        clearChineseCache();
    }
}

void KeyboardForm::btnEmojiClicked()
{
    emit sendKeyToFocusItem("::)");
}

void KeyboardForm::characterButtonClicked()
{
    if(current_mode == InputMode::zh)
    {
        if(((QPushButton*)sender())->text() == "，" || ((QPushButton*)sender())->text() == "。" || ((QPushButton*)sender())->text() == "？")
        {
            emit sendKeyToFocusItem(((QPushButton*)sender())->text());
        }
        else
        {
            if(m_label_pinyin->text().length()<15)
            {
                m_label_pinyin->setText(m_label_pinyin->text().append(((QPushButton*)sender())->text()));
                searchChineseCharacters(0);
                updateButtonStateOfChineseCharacters();
            }
        }
    }
    else
    {
        emit sendKeyToFocusItem(((QPushButton*)sender())->text());
    }
}

void KeyboardForm::searchChineseCharacters(const int &currentpage)
{
    const int max_spelling_length = 32;
    const int max_decoded_length = 32;
    const int max_single_hanzi = 20;
    static unsigned int page_change_times = 0;

    QString app_dir(qApp->applicationDirPath()+"/dict");
    im_open_decoder(QString("%1/dict_pinyin.dat").arg(app_dir).toLocal8Bit().data(),
                    QString("%1/dict_pinyin_user.dat").arg(app_dir).toLocal8Bit().data());

    im_set_max_lens(max_spelling_length, max_decoded_length);
    im_reset_search();

    QByteArray bytearray(m_label_pinyin->text().toUtf8());
    char *pinyin(bytearray.data());
    size_t cand_num = im_search(pinyin, bytearray.size());

    size_t decode_len;
    im_get_sps_str(&decode_len);
    if (decode_len == 1)
    {
        if (cand_num > 10) cand_num = 10;
    }
    else
    {
        size_t single = 0;
        size_t multi = 0;
        char16 *cand_buf = new char16[max_decoded_length];
        for(size_t i = 0; i < cand_num; i++)
        {
            im_get_candidate(i, cand_buf, max_decoded_length);
            if (strlen((char *)cand_buf) > 2)
            {
                multi++;
            }
            else
            {
                single++;
                if (single > max_single_hanzi) break;
            }
        }
        cand_num = multi + single;
        delete cand_buf;
    }

    switch(currentpage)
    {
    case 1:
        if(cand_num > chinese_characters_list.length() && page_change_times < cand_num - chinese_characters_list.length())
            page_change_times++;
        break;
    case -1:
        if(page_change_times > 0) page_change_times--;
        break;
    default:
        page_change_times = 0;
        break;
    }
    if(0 == page_change_times)
        change_chinese_characters_page_list.at(0)->setEnabled(false);
    else
        change_chinese_characters_page_list.at(0)->setEnabled(true);
    if(page_change_times == cand_num - chinese_characters_list.length())
        change_chinese_characters_page_list.at(1)->setEnabled(false);
    else
        change_chinese_characters_page_list.at(1)->setEnabled(true);

    char16 *cand_buf = new char16[max_decoded_length];
    char16 *cand;
    QString cand_str;
    for (unsigned i = 0; i < cand_num; i++)
    {
        cand = im_get_candidate(i, cand_buf, max_decoded_length);
        if (cand)
        {
            cand_str = QString::fromUtf16(cand);
            if (i == 0) cand_str.remove(0, im_get_fixed_len());
        }
        else
        {
            cand_str = "";
        }
        int tmpindex = i - page_change_times;
        if(tmpindex >= 0 && tmpindex < chinese_characters_list.length())
        {
            switch(currentpage)
            {
            case 1:
                chinese_characters_list.at(tmpindex)->setText(cand_str);
                break;
            case -1:
                chinese_characters_list.at(tmpindex)->setText(cand_str);
                break;
            default:
                chinese_characters_list.at(tmpindex)->setText(cand_str);
                break;
            }
        }
    }
    delete cand_buf;
}
