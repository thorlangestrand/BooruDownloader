#ifndef WARN_H
#define WARN_H

#include <QString> // IWYU pragma: export
#include <QMessageBox> // IWYU pragma: export

///
/// \brief Warn
///
/// Display a warning message box to screen
/// with a message
///
/// \param msg - Message displayed in message box
///
void Warn(QString msg);

#endif // WARN_H
