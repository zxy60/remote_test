#include "caculator.h"
#include <iostream>
#include <limits>

// 函数声明，用于各个子菜单
void vectorMenu();
void polynomialMenu_Sequential();
void polynomialMenu_Chained();

int main() {
    int choice;
    while (true) {
        // 主菜单
        std::cout << "\n\n--- C++ 计算器主菜单 ---\n";
        std::cout << "1. 向量计算器 (顺序表实现)\n";
        std::cout << "2. 多项式计算器 (顺序表实现)\n";
        std::cout << "3. 多项式计算器 (链表实现)\n";
        std::cout << "4. 四则运算 (不含变量)\n";
        std::cout << "5. 四则运算 (含单变量)\n";
        std::cout << "0. 退出程序\n";
        std::cout << "--------------------------\n";
        std::cout << "请输入您的选择: ";
        
        std::cin >> choice;

        // 检查输入是否为有效数字
        if (std::cin.fail()) {
            std::cout << "\n[错误] 无效输入，请输入一个数字。\n";
            std::cin.clear(); // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空输入缓冲区
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    vectorMenu();
                    break;
                case 2:
                    polynomialMenu_Sequential();
                    break;
                case 3:
                    polynomialMenu_Chained();
                    break;
                case 4:
                    basicArithmetic(0); // 调用不含变量的四则运算
                    break;
                case 5:
                    basicArithmetic(1); // 调用含变量的四则运算
                    break;
                case 0:
                    std::cout << "感谢使用，程序退出。\n";
                    return 0;
                default:
                    std::cout << "\n[错误] 无效选择，请输入 0-5 之间的数字。\n";
                    break;
            }
        } catch (const std::exception& e) {
            // 捕获并打印在 caculator.h 中可能抛出的所有异常
            std::cerr << "\n[运行时错误]: " << e.what() << '\n';
        }
    }
    return 0;
}

// 1. 向量计算器子菜单
void vectorMenu() {
    int dim;
    std::cout << "\n--- 向量计算 ---\n";
    std::cout << "请输入向量的维度: ";
    std::cin >> dim;
    if (dim <= 0) {
        std::cout << "[错误] 维度必须是正整数。\n";
        return;
    }

    vec_s vec1(dim), vec2(dim);
    std::cout << "请输入第一个向量的 " << dim << " 个元素 (以空格分隔): ";
    vec1.update();
    std::cout << "请输入第二个向量的 " << dim << " 个元素 (以空格分隔): ";
    vec2.update();

    // 加法
    std::cout << "\n向量相加 (vec1 + vec2) 结果: ";
    vec_s sum = vec1 + vec2;
    sum.iterate();
    std::cout << std::endl;

    // 减法
    std::cout << "向量相减 (vec1 - vec2) 结果: ";
    vec_s diff = vec1 - vec2;
    diff.iterate();
    std::cout << std::endl;

    // 余弦相似度
    std::cout << "余弦相似度结果: " << vec1.cosSimilarity(vec2) << std::endl;
}

// 2. 多项式计算器子菜单 (顺序表)
void polynomialMenu_Sequential() {
    std::cout << "\n--- 多项式计算 (顺序表实现) ---\n";
    std::cout << "创建第一个多项式:\n";
    poly_s poly1;
    std::cout << "创建第二个多项式:\n";
    poly_s poly2;

    std::cout << "\n第一个多项式为: ";
    poly1.iterate();
    std::cout << "第二个多项式为: ";
    poly2.iterate();

    // 加法
    std::cout << "\n多项式相加 (poly1 + poly2) 结果: ";
    poly_s sum = poly1 + poly2;
    sum.iterate();

    // 减法
    std::cout << "多项式相减 (poly1 - poly2) 结果: ";
    poly_s diff = poly1 - poly2;
    diff.iterate();

    // 乘法
    std::cout << "多项式相乘 (poly1 * poly2) 结果: ";
    poly_s prod = poly1 * poly2;
    prod.iterate();

    // 求导
    int order;
    std::cout << "\n请输入要求解的导数阶数 (例如: 1 表示一阶导): ";
    std::cin >> order;
    if (order >= 0) {
        poly_s deriv = poly1;
        for (int i = 0; i < order; ++i) {
            deriv = deriv.differentiate();
        }
        std::cout << "第一个多项式的 " << order << " 阶导数是: ";
        deriv.iterate();
    }
}

// 3. 多项式计算器子菜单 (链表)
void polynomialMenu_Chained() {
    std::cout << "\n--- 多项式计算 (链表实现) ---\n";
    std::cout << "创建第一个多项式:\n";
    poly_c poly1;
    std::cout << "创建第二个多项式:\n";
    poly_c poly2;

    std::cout << "\n第一个多项式为: ";
    poly1.iterate();
    std::cout << "第二个多项式为: ";
    poly2.iterate();

    // 加法
    std::cout << "\n多项式相加 (poly1 + poly2) 结果: ";
    poly_c sum = poly1 + poly2;
    sum.iterate();

    // 减法
    std::cout << "多项式相减 (poly1 - poly2) 结果: ";
    poly_c diff = poly1 - poly2;
    diff.iterate();

    // 乘法
    std::cout << "多项式相乘 (poly1 * poly2) 结果: ";
    poly_c prod = poly1 * poly2;
    prod.iterate();

    // 求导
    int order;
    std::cout << "\n请输入要求解的导数阶数 (例如: 1 表示一阶导): ";
    std::cin >> order;
    if (order >= 0) {
        poly_c deriv = poly1;
        for (int i = 0; i < order; ++i) {
            deriv = deriv.differentiate();
        }
        std::cout << "第一个多项式的 " << order << " 阶导数是: ";
        deriv.iterate();
    }
}