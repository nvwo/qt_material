最近需要使用qtest编写一些测试,所以到https://doc.qt.io/qt-5/qtest-tutorial.html

第一章: 编写单元测试
===========

如何编写单元测试。

在第一章中，我们将看到如何为类编写一个简单的单元测试，以及如何执行它。

#### 写作测试

假设您想要测试我们的 QString 类的行为。首先，您需要一个包含测试函数的类。这个类必须从 QObject 继承:

```
#include <QtTest/QtTest>

class TestQString: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};
```

注意: 您需要包含 QTest 头，并将测试函数声明为私有槽，以便测试框架查找并执行它。

然后你需要实现测试函数本身:

```
void TestQString::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}
```

宏计算作为其参数传递的表达式。如果表达式的计算结果为 true，则测试函数的执行将继续。否则，将在测试日志中附加描述故障的消息，并且测试函数将停止执行。

但是如果你想要测试日志更详细的输出，你应该使用 QCOMPARE ()宏来代替:

```
void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}
```

如果两个字符串不相等，那么两个字符串的内容将被追加到测试日志中，这样就可以立即看到比较失败的原因。

最后，要使我们的测试用例成为独立的可执行文件，需要以下两行代码:

```
QTEST_MAIN(TestQString)
#include "testqstring.moc"
```

宏扩展为运行所有测试函数的简单 main ()方法。注意，如果我们的测试类的声明和实现都在。在 cpp 文件中，我们还需要包含生成的 moc 文件，以使 Qt 的内省工作。

#### 执行测试

现在我们已经完成了测试的编写，我们想要执行它。假设我们的测试被保存为一个空目录中的 testqstring.cpp，我们使用 qmake 来创建一个项目并生成一个 makefile。

```
/myTestDirectory$ qmake -project "QT += testlib"
/myTestDirectory$ qmake
/myTestDirectory$ make
```

注意: 如果你使用 windows，用 nmake 或者任何你使用的构建工具替换 make。

运行生成的可执行文件应该会给您以下输出:

```
********* Start testing of TestQString *********
Config: Using QtTest library %VERSION%, Qt %VERSION%
PASS   : TestQString::initTestCase()
PASS   : TestQString::toUpper()
PASS   : TestQString::cleanupTestCase()
Totals: 3 passed, 0 failed, 0 skipped
********* Finished testing of TestQString *********
```

恭喜您! 您刚刚使用 Qt 测试框架编写并执行了您的第一个单元测试。

第三章: 模拟 GUI 事件
==============

如何模拟 GUI 事件。

Qt 测试提供了一些测试图形用户界面的机制。Qt 测试不是模拟本机窗口系统事件，而是发送内部 Qt 事件。这意味着在运行测试的机器上没有副作用。

在本章中，我们将看到如何编写一个简单的 GUI 测试。

这一次，让我们假设您想要测试 QLineEdit 类的行为。和之前一样，你需要一个包含你的测试函数的类:

```
#include <QtWidgets>
#include <QtTest/QtTest>

class TestGui: public QObject
{
    Q_OBJECT

private slots:
    void testGui();

};
```

唯一的区别是，除了 QTest 名称空间之外，您还需要包含 Qt GUI 类定义。

```
void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}
```

在测试函数的实现中，我们首先创建一个 QLineEdit。然后，我们使用 QTest: : keyClicks ()函数在行编辑中模拟编写" hello world"。

注意: 为了正确测试键盘快捷键，还必须显示小部件。

keyClicks ()模拟单击小部件上的一系列键。可选地，可以指定键盘修饰符以及每次单击键后测试的延迟(以毫秒为单位)。类似地，您可以使用 QTest: : keyClick ()、 QTest: : keyPress ()、 QTest: : keyRelease ()、 QTest: : : mouseClick ()、 QTest: : : mouseDClick ()、 QTest: : mouseemove ()、 QTest: : mousePress ()和 QTest: : mouseRelease ()函数来模拟相关的 GUI 事件。

最后，我们使用 QCOMPARE ()宏来检查行编辑的文本是否符合预期。

与前面一样，要使我们的测试用例成为独立的可执行文件，需要以下两行代码:

```
QTEST_MAIN(TestGui)
#include "testgui.moc"
```

宏扩展为运行所有测试函数的简单 main ()方法，因为我们测试类的声明和实现都在。在 cpp 文件中，我们还需要包含生成的 moc 文件，以使 Qt 的内省工作。

第四章: 回放 GUI 事件
==============

如何重放 GUI 事件。

在本章中，我们将展示如何模拟 GUI 事件，以及如何存储一系列 GUI 事件并在小部件上重播它们。

存储一系列事件并重放它们的方法与第2章中解释的方法非常相似。你所需要做的就是在你的测试类中添加一个数据函数:

```
class TestGui: public QObject
{
    Q_OBJECT

private slots:
    void testGui_data();
    void testGui();
};
```

#### 编写数据函数

与前面一样，测试函数的关联数据函数带有相同的名称，并由 _ data 附加。

```
void TestGui::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there and back again") << list2 << "";
}
```

首先，我们使用 QTest: : addColumn ()函数定义表的元素: GUI 事件的列表，以及在 QWidget 上应用事件列表的预期结果。注意，第一个元素的类型是 QTestEventList。

QTestEventList 可以使用 GUI 事件填充，这些事件可以作为测试数据存储以供以后使用，也可以在任何 QWidget 上重播。

在当前的数据函数中，我们创建了两个 QTestEventList 元素。第一个列表包含单击" a"键。我们使用 QTestEventList: : addKeyClick ()函数将事件添加到列表中。然后，我们使用 QTest: : newRow ()函数为数据集提供一个名称，并将事件列表和预期结果流输入表中。

第二个列表包含两个按键单击: a 和后面的退格键。我们再次使用 QTestEventList: : addKeyClick ()将事件添加到列表中，并使用 QTest: : newRow ()将事件列表和预期结果放入具有相关名称的表中。

#### 重写测试函数

我们的测试现在可以重写:

```
void TestGui::testGui()
{
    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    QLineEdit lineEdit;

    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}
```

TestGui: : TestGui ()函数将执行两次，对于我们在相关的 TestGui: : TestGui _ data ()函数中创建的测试数据中的每个条目执行一次。

首先，我们使用 QFETCH ()宏获取数据集的两个元素。QFETCH ()接受两个参数: 元素的数据类型和元素名称。然后，我们创建一个 QLineEdit，并使用 QTestEventList: : simulate ()函数在该小部件上应用事件列表。

最后，我们使用 QCOMPARE ()宏来检查行编辑的文本是否符合预期。

与前面一样，要使我们的测试用例成为独立的可执行文件，需要以下两行代码:

```
QTEST_MAIN(TestGui)
#include "testgui.moc"
```

宏扩展为运行所有测试函数的简单 main ()方法，因为我们测试类的声明和实现都在。在 cpp 文件中，我们还需要包含生成的 moc 文件，以使 Qt 的内省工作。

参考:

<https://blog.csdn.net/yizhou2010/article/details/78272505>

<https://github.com/CppCon/CppCon2020/blob/main/Presentations/quickly_testing_qt_desktop_applications_with_approval_tests/quickly_testing_qt_desktop_applications_with_approval_tests__clare_macrae__cppcon_2020.pdf>

<https://raw.githubusercontent.com/CppCon/CppCon2020/main/Presentations/quickly_testing_qt_desktop_applications_with_approval_tests/quickly_testing_qt_desktop_applications_with_approval_tests__clare_macrae__cppcon_2020.pdf>

<https://github.com/e-j/qt-multiple-tests>

<https://8bitscoding.github.io/qt/core/QtTest/>

<https://doc.qt.io/qtcreator/creator-autotest.html>

<https://doc.qt.io/qt-5/qtest-tutorial.html>

关于测试工程的项目结构:  
<https://stackoverflow.com/questions/12154980/how-to-structure-project-while-unit-testing-qt-app-by-qtestlib>
