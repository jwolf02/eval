#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <calc.hpp>
#include <sstream>

static void print_help() {
  std::cout << "Usage: calc [expression [expression] ...]" << std::endl;
  std::cout << "Functions and Operators:" << std::endl;
  std::cout << "Basic arithmethic:  +, -, *, /, ^, mod" << std::endl;
  std::cout << "Trigonometrics:     sin(x), cos(x), tan(x), asin(x), acos(x), atan(x), cot(a)" << std::endl;
  std::cout << "Hyperbolics:        sinh(x), cosh(x), tanh(x), asinh(x), acosh(x), atanh(x)" << std::endl;
  std::cout << "Exponentials:       sqr(x), sqrt(x), cbrt(x), root(n, x), exp(x)" << std::endl;
  std::cout << "Logarithms:         log2(x), log10(x), ln(x), log(b, e)" << std::endl;
  std::cout << "Miscelleneous:      min(a, b), max(a, b), sign(x), hypot(x, y)" << std::endl;
  std::cout << "Rounding functions: ceil(x), floor(x), abs(x), trunc(x)" << std::endl;
  std::cout << "Combinatorics:      n!, binomial(n, k)" << std::endl;
  std::cout << "Circle and Ball:    circumference(r), circle_area(r), ball_volume(r), ball_surface(r)" << std::endl;
  std::cout << "Constants:          e, pi, inf" << std::endl;
}

static std::string strip_trailing_zeros(const std::string &result) {
    std::string str;
    if (result.find('.') != std::string::npos) {
        int i = (int) result.size() - 1;
        while (i >= 0 and result[i] == '0')
            --i;
        str = result[i] == '.' ? result.substr(0, (unsigned long) i) : result.substr(0, (unsigned long) i + 1);
    } else {
        str = result;
    }

    return str != "-0" ? str : "0";
}

static std::string to_string(double r) {
  std::stringstream oss;
  oss << std::fixed << std::setprecision(15) << r;
  std::string str;
  oss >> str;
  return strip_trailing_zeros(str);
}

int main(int argc, const char *argv[]) {
  if (argc > 1 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
    print_help();
    exit(EXIT_SUCCESS);
  }

  // batch mode
  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      try {
        if (argc > 2)
          std::cout << '(' << i << ") ";
        std::cout << to_string(calc::evaluate(argv[i])) << std::endl;
      } catch (std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
      }
    }
    return 0;
  }

  std::string last_expr;

  // interactive mode
  while (true) {
    std::cout << "> " << std::flush;

    std::string expr;
    std::getline(std::cin, expr);
    if (!expr.empty()) {
      // exit
      if (expr == "q" || expr == "quit") {
        break;
      } else if (expr == "!!") {
        expr = last_expr;
      }

      try {
        last_expr = expr;
        // evaluate entered expression
        std::cout << to_string(calc::evaluate(expr)) << std::endl;
      } catch (std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
