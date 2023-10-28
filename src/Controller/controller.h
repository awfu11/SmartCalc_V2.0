#ifndef SMARTCALC_SRC_CONTROLLER_CONTROLLER_H_
#define SMARTCALC_SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"

namespace awfl {
class Controller {
 public:
  Controller() = default;
  Controller(Model* m) : model(m) {}
  ~Controller() = default;

  std::pair<int, double> calculate(const std::string& eq, const double& var = 0.0) {
    model->set(eq, var);
    return model->calculateReversePN();
  }

 private:
  Model* model;
};

}  // namespace awfl

#endif  // SMARTCALC_SRC_CONTROLLER_CONTROLLER_H_
