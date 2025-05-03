#include "mainwindow.h"
#include "./ui_mainwindow.h" // Note the path for the generated UI header
#include <QLocale> // For formatting numbers

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // You could connect the button's clicked() signal to the slot here
    // connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::on_calculateButton_clicked);
    // But Qt's auto-connection mechanism handles this due to the naming convention "on_widgetName_signalName"
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculateButton_clicked()
{
    // Get values from UI elements
    int target_enhanced = ui->targetEnhancedSpinBox->value();
    int current_enhanced = ui->currentEnhancedSpinBox->value();
    double enhanced_price = ui->enhancedPriceSpinBox->value();
    double normal_price = ui->normalPriceSpinBox->value();

    // Constants
    const int normal_per_enhanced = 160; // 32 * 5 from original script

    // Calculations
    int needed_enhanced = target_enhanced - current_enhanced;
    if (needed_enhanced < 0) {
        needed_enhanced = 0; // Can't need negative items
    }

    long long needed_normal = static_cast<long long>(needed_enhanced) * normal_per_enhanced; // Use long long for potentially large numbers
    double total_cost_normal = needed_normal * normal_price;
    double total_cost_enhanced = needed_enhanced * enhanced_price;

    // Use QLocale for currency formatting
    QLocale locale(QLocale::English, QLocale::UnitedStates); // Or another appropriate locale

    // Update result labels
    ui->resultNeededEnhancedLabel->setText(QString("Enhanced items needed: %1").arg(needed_enhanced));
    ui->resultNeededNormalLabel->setText(QString("Normal items needed to craft: %L1").arg(needed_normal)); // %L1 for localized long long
    ui->resultCostEnhancedLabel->setText(QString("Cost if buying Enhanced directly: %1").arg(locale.toCurrencyString(total_cost_enhanced)));
    ui->resultCostNormalLabel->setText(QString("Cost if buying Normal and crafting: %1").arg(locale.toCurrencyString(total_cost_normal)));

    // Update recommendation label
    if (needed_enhanced <= 0) {
         ui->recommendationLabel->setText("💡 Recommendation: You already have enough or more than the target!");
    } else if (total_cost_normal < total_cost_enhanced) {
        ui->recommendationLabel->setText("💡 Recommendation: 👉 Buying Normal items and crafting is cheaper!");
    } else if (total_cost_enhanced < total_cost_normal) {
        ui->recommendationLabel->setText("💡 Recommendation: 👉 Buying Enhanced items directly is cheaper!");
    } else {
         ui->recommendationLabel->setText("💡 Recommendation: 👉 Both methods cost the same. Choose based on convenience!");
    }
}

// Slot implementation for the Reset button
void MainWindow::on_resetButton_clicked()
{
    // Reset input fields to 0
    ui->targetEnhancedSpinBox->setValue(0);
    ui->currentEnhancedSpinBox->setValue(0);
    ui->enhancedPriceSpinBox->setValue(0.0);
    ui->normalPriceSpinBox->setValue(0.0);

    // Reset result labels to their initial state
    ui->resultNeededEnhancedLabel->setText("Enhanced items needed: -");
    ui->resultNeededNormalLabel->setText("Normal items needed to craft: -");
    ui->resultCostEnhancedLabel->setText("Cost if buying Enhanced directly: $ -");
    ui->resultCostNormalLabel->setText("Cost if buying Normal and crafting: $ -");

    // Reset recommendation label
    ui->recommendationLabel->setText("💡 Recommendation: -");
}

