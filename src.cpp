#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ARIMA function to predict next value
double predictNextValue(vector<double>& data, int p, int d, int q) {
    // Initialize the model parameters
    vector<double> ar(p), ma(q);
    double c = 0.0;
    double residual = 0.0;

    // Initialize the differenced data vector
    vector<double> diff_data(data.size() - d);
    for (int i = d; i < data.size(); i++) {
        diff_data[i - d] = data[i] - data[i - d];
    }

    // Estimate the AR coefficients using Yule-Walker equations
    for (int i = 0; i < p; i++) {
        double sum = 0.0;
        for (int j = i; j < diff_data.size(); j++) {
            sum += diff_data[j] * diff_data[j - i];
        }
        ar[i] = sum / (diff_data.size() - i);
    }

    // Estimate the MA coefficients using least squares regression
    vector<double> x(q);
    for (int i = 0; i < q; i++) {
        x[i] = diff_data[diff_data.size() - i - 1];
    }
    vector<double> y(q);
    for (int i = 0; i < q; i++) {
        y[i] = diff_data[diff_data.size() - i - 2];
    }
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xx = 0.0;
    for (int i = 0; i < q; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
    }
    double slope = (q * sum_xy - sum_x * sum_y) / (q * sum_xx - sum_x * sum_x);
    ma[0] = slope;

    // Estimate the constant term using the estimated coefficients and residual
    for (int i = p; i < data.size(); i++) {
        double predicted = c;
        for (int j = 0; j < p; j++) {
            predicted += ar[j] * (data[i - j - 1] - c);
        }
        for (int j = 1; j < q; j++) {
            if (i - j - 1 < 0) {
                break;
            }
            predicted += ma[j] * residual;
        }
        residual = diff_data[i - d] - predicted;
        c += residual / (i - p + 1);
    }

    // Predict the next value of the time series
    double forecast = c;
    for (int i = 1; i <= p; i++) {
        forecast += ar[i - 1] * (data[data.size() - i] - c);
    }
    for (int i = 1; i < q; i++) {
        forecast += ma[i] * residual;
    }
    return forecast + data[data.size() - 1];
}

int main()
{
    // Load the time series data
    vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0};
  
  // Set the ARIMA model parameters
int p = 2;
int d = 1;
int q = 1;

// Predict the next value of the time series
double nextValue = predictNextValue(data, p, d, q);

// Output the predicted value
cout << "The next value in the time series is: " << nextValue << endl;

return 0;
}
