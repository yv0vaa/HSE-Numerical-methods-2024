#include "../include/Differentiator.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

using DoubleFuncPtr = double(*)(double, double);
using AADFuncPtr = AAD22(*)(AAD22, AAD22);


void test_functions(DoubleFuncPtr f, AADFuncPtr F, double x, double y) {
    int width = 13;
    std::cout << "     " << "   stencil3   | stencil3Extra |    stencil5   | stencil5Extra |     FwdAAD\n";
    std::cout << "-----------------------------------------------------------------------------------\n";

    std::cout << "dx:  " <<  std::setw(width)
    << Differentiator<WhichD::X, DiffMethod::Stencil3>(f, x, y) << " | " 
    << std::setw(width)
    << Differentiator<WhichD::X, DiffMethod::Stencil3Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::X, DiffMethod::Stencil5>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::X, DiffMethod::Stencil5Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::X, DiffMethod::FwdAAD>(F, x, y) << "\n";

    std::cout << "dy:  " << std::setw(width)
    << Differentiator<WhichD::Y, DiffMethod::Stencil3>(f, x, y) << " | " 
    << std::setw(width)
    << Differentiator<WhichD::Y, DiffMethod::Stencil3Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::Y, DiffMethod::Stencil5>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::Y, DiffMethod::Stencil5Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::Y, DiffMethod::FwdAAD>(F, x, y) << "\n";

    std::cout << "dxx: " << std::setw(width)
    << Differentiator<WhichD::XX, DiffMethod::Stencil3>(f, x, y) << " | " 
    << std::setw(width)
    << Differentiator<WhichD::XX, DiffMethod::Stencil3Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::XX, DiffMethod::Stencil5>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::XX, DiffMethod::Stencil5Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::XX, DiffMethod::FwdAAD>(F, x, y) << "\n";

    std::cout << "dyy: " << std::setw(width)
    << Differentiator<WhichD::YY, DiffMethod::Stencil3>(f, x, y) << " | " 
    << std::setw(width)
    << Differentiator<WhichD::YY, DiffMethod::Stencil3Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::YY, DiffMethod::Stencil5>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::YY, DiffMethod::Stencil5Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::YY, DiffMethod::FwdAAD>(F, x, y) << "\n";

    std::cout << "dxy: " << std::setw(width)
    << std::setw(width)
    << Differentiator<WhichD::XY, DiffMethod::Stencil3>(f, x, y) << " | " 
    << std::setw(width)
    << Differentiator<WhichD::XY, DiffMethod::Stencil3Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::XY, DiffMethod::Stencil5>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::XY, DiffMethod::Stencil5Extra>(f, x, y) << " | "
    << std::setw(width)
    << Differentiator<WhichD::XY, DiffMethod::FwdAAD>(F, x, y) << "\n";
}

double f1(double x, double y) { return x * x + y * y; }
double f2(double x, double y) { return x * x * x - y / x; }
double f3(double x, double y) { return ((10 * x - 1) * y) / (x - y * y); }
double f4(double x, double y) { return std::sin(x / y); }
double f5(double x, double y) { return std::cos(3.3 * x * y); }
double f6(double x, double y) { return std::exp(0.5 * x * x + y / 3); }
double f7(double x, double y) { return std::exp(std::cos(x / (0.3 * y)) + std::sin(35 * std::exp(y - 0.2))); }

AAD22 F1(AAD22 x, AAD22 y) { return x * x + y * y; }
AAD22 F2(AAD22 x, AAD22 y) { return x * x * x - y / x; }
AAD22 F3(AAD22 x, AAD22 y) { return ((10 * x - 1) * y) / (x - y * y); }
AAD22 F4(AAD22 x, AAD22 y) { return sin(x / y); }
AAD22 F5(AAD22 x, AAD22 y) { return cos(3.3 * x * y); }
AAD22 F6(AAD22 x, AAD22 y) { return exp(0.5 * x * x + y / 3); }
AAD22 F7(AAD22 x, AAD22 y) { return exp(cos(x / (0.3 * y)) + sin(35 * exp(y - 0.2))); }

std::vector<DoubleFuncPtr> double_funcs = {f1, f2, f3, f4, f5, f6, f7};
std::vector<AADFuncPtr> AAD22_funcs = {F1, F2, F3, F4, F5, F6, F7};

int main() {
    double x = 2.1, y = 0.7;
    std::cout << "TESTING at (" << x << ", " << y << ")\n";
    for (int i = 0; i < double_funcs.size(); i++) {
        std::cout << "Function " << i + 1 << ":\n";
        std::cout << "===================================================================================\n";
        test_functions(double_funcs[i], AAD22_funcs[i], x, y);
        std::cout << "===================================================================================\n";
    }
}