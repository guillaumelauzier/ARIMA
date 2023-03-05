#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
  // Load the time series data
  vec data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

  // Specify the order of the ARIMA model
  int p = 1; // Order of the AR component
  int d = 1; // Order of the differencing operation
  int q = 1; // Order of the MA component

  // Create an ARIMA model object
  arma::arima::ARIMA<arma::vec> model(data);
  model.order(arma::uvec{p, d, q});

  // Fit the model to the data
  arma::arima::ARIMAResults<arma::vec> results = model.fit();

  // Print the model coefficients and residuals
  cout << "ARIMA coefficients: " << results.ar << endl;
  cout << "MA coefficients: " << results.ma << endl;
  cout << "Intercept: " << results.const_term << endl;
  cout << "Residuals: " << results.resid << endl;

  // Predict the next value of the time series
  double forecast = results.predict();
  cout << "Next value prediction: " << forecast << endl;

  return 0;
}
