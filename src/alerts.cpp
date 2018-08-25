#include "alerts.h"
#include "ui_alerts.h"
#include "logger.h"
#include "ledindicator.h"

#define CLASS_INFO  "alerts"


Alerts::Alerts(QWidget *parent) :
    QWidget(parent),
    controller(new Ui::Alerts)
{
    LOG (LOG_ALERTS, "%s - in contructor", CLASS_INFO);

    controller->setupUi(this);
    this->initControllerErrors();
    this->initControllerWidget();

}

Alerts::~Alerts()
{
    delete controller;
}

void Alerts::initControllerWidget(void)
{
    LOG (LOG_ALERTS, "%s - initializing controller widget", CLASS_INFO);
    int ledNumber;

    ledSlots = this->findChildren<QFrame *>();
    for (int i = 0; i < ledSlots.size(); ++i) {
        if (ledSlots.at(i) != NULL) {
            if (ledSlots.at(i)->objectName().contains("led_err", Qt::CaseSensitive)) {
                LOG (LOG_ALERTS, "%s - found %s", CLASS_INFO, \
                     ledSlots.at(i)->objectName().toStdString().c_str());
                /* draw new led */
                led = new LedIndicator(ledSlots.at(i));
                led->setGeometry(20, 0, 30, 30);
                leds.append(ledSlots.at(i)->objectName());
            } else if (ledSlots.at(i)->objectName().contains("label_err", Qt::CaseSensitive)) {
                LOG (LOG_ALERTS, "%s - found %s", CLASS_INFO, \
                     ledSlots.at(i)->objectName().toStdString().c_str());
                ledNumber = ledSlots.at(i)->objectName().replace("label_err", "").toInt();
                QLabel *label = qobject_cast<QLabel *>(ledSlots.at(i));
                label->setText(controllerErrors[ledNumber]);
            }
        }
    }
}


void Alerts::initControllerErrors(void)
{
    LOG (LOG_ALERTS, "%s - initializing controller errors", CLASS_INFO);

    controllerErrors[0] = "Identification error";
    controllerErrors[1] = "Over Voltage";
    controllerErrors[2] = "Low Voltage";
    controllerErrors[3] = "RESERVED";
    controllerErrors[4] = "Motor provice speed feedback";
    controllerErrors[5] = "Internal volts fault";
    controllerErrors[6] = "Over temperature";
    controllerErrors[7] = "Throttle error at power-up";
    controllerErrors[8] = "RESERVED";
    controllerErrors[9] = "Internal reset";
    controllerErrors[10] = "Hall throttle open";
    controllerErrors[11] = "Angle sensor open";
    controllerErrors[12] = "RESERVED";
    controllerErrors[13] = "RESERVED";
    controllerErrors[14] = "Motor over temperature";
    controllerErrors[15] = "Hall Galvanometer sensor error";
}
