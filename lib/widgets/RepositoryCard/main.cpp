#include <qtimer.h>

#include <QApplication>
// #include <QDebug>
// #include <QThread>

// #include "Faker.hpp"

// class Worker : public QThread {
//     Q_OBJECT
//     Q_DISABLE_COPY_MOVE(Worker)
//   public:
//     Worker() = default;
//     ~Worker() = default;

//   protected:
//     void run() override {
//         for (int i = 0; i < 3; i++) {
//             auto lorem = faker.GetLorem();
//             auto hacker = faker.GetHacker();
//             qDebug() << "Thread:" << QThread::currentThreadId()
//                      << "Lorem(" << i << "):" << QString::fromStdString(lorem)
//                      << "Hacker(" << i << "):" << QString::fromStdString(hacker);
//         }
//     }

//   private:
//     Faker faker;
// };

#include "RepositoryCard.hpp"
#include "RepositoryTableView.hpp"

int main(int argc, char *argv[]) {
    // QApplication app(argc, argv);
    // Worker worker1;
    // Worker worker2;

    // worker1.start();
    // worker2.start();

    // worker1.wait();
    // worker2.wait();
    // return app.exec();
    QApplication app(argc, argv);
    RepositoryCard card;
    card.show();
    // RepoTableView view;
    // view.show();
    return app.exec();
}

// #include "main.moc"