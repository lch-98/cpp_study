/*
 * [Topic] Test Fixtures & TDD Cycle
 * 테스트 픽스처로 공통 상태를 재사용하고, TDD 사이클을 경험한다.
 *
 * TDD (Test-Driven Development) 사이클:
 *   1. Red   : 실패하는 테스트 먼저 작성
 *   2. Green : 테스트가 통과하는 최소한의 코드 작성
 *   3. Refactor : 코드 품질 개선 (테스트가 계속 통과해야 함)
 *
 * gtest Fixture:
 *   class MyTest : public ::testing::Test {
 *       void SetUp() override { /* 각 테스트 전 실행 */ }
 *       void TearDown() override { /* 각 테스트 후 실행 */ }
 *   };
 *   TEST_F(MyTest, TestName) { ... }
 *
 * Practice:
 *   - Stack 클래스에 대한 테스트 픽스처 직접 작성
 *   - push → pop → empty 순서 테스트
 */
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

// ===== TDD로 만들 클래스: ShoppingCart =====
class ShoppingCart {
    struct Item { string name; double price; int qty; };
    vector<Item> items;
public:
    void add(const string& name, double price, int qty = 1) {
        for (auto& item : items) {
            if (item.name == name) { item.qty += qty; return; }
        }
        items.push_back({name, price, qty});
    }
    void remove(const string& name) {
        items.erase(remove_if(items.begin(), items.end(),
            [&](const Item& i){ return i.name == name; }), items.end());
    }
    double total() const {
        double sum = 0;
        for (const auto& i : items) sum += i.price * i.qty;
        return sum;
    }
    int count() const {
        int n = 0;
        for (const auto& i : items) n += i.qty;
        return n;
    }
    bool empty() const { return items.empty(); }
    void clear() { items.clear(); }
};

// ===== 픽스처 시뮬레이션 =====
int pass_count = 0, fail_count = 0;

#define EXPECT_EQ(a, b) do { \
    if ((a) == (b)) { cout << "  PASS\n"; pass_count++; } \
    else { cout << "  FAIL: " << (a) << " != " << (b) << " (line " << __LINE__ << ")\n"; fail_count++; } \
} while(0)

#define EXPECT_NEAR(a, b, e) do { \
    if (abs((a)-(b)) < (e)) { cout << "  PASS\n"; pass_count++; } \
    else { cout << "  FAIL: " << (a) << " != " << (b) << "\n"; fail_count++; } \
} while(0)

#define EXPECT_TRUE(a)  EXPECT_EQ(!!(a), true)
#define EXPECT_FALSE(a) EXPECT_EQ(!!(a), false)

struct CartFixture {
    ShoppingCart cart;
    void SetUp() {
        cart.clear();
        cart.add("Apple", 1.5, 3);
        cart.add("Banana", 0.8, 2);
    }
};

void run_test(const string& name, auto fn) {
    cout << "[" << name << "]\n";
    fn();
}

int main() {
    // TDD: Red → Green → Refactor 시뮬레이션
    run_test("빈 카트", [](){
        ShoppingCart cart;
        EXPECT_TRUE(cart.empty());
        EXPECT_EQ(cart.count(), 0);
        EXPECT_NEAR(cart.total(), 0.0, 0.001);
    });

    run_test("상품 추가", [](){
        CartFixture f; f.SetUp();
        EXPECT_FALSE(f.cart.empty());
        EXPECT_EQ(f.cart.count(), 5);  // 3 + 2
        EXPECT_NEAR(f.cart.total(), 1.5*3 + 0.8*2, 0.001);
    });

    run_test("같은 상품 추가", [](){
        ShoppingCart cart;
        cart.add("Apple", 1.5, 2);
        cart.add("Apple", 1.5, 3);
        EXPECT_EQ(cart.count(), 5);
    });

    run_test("상품 제거", [](){
        CartFixture f; f.SetUp();
        f.cart.remove("Apple");
        EXPECT_EQ(f.cart.count(), 2);
        EXPECT_NEAR(f.cart.total(), 0.8*2, 0.001);
    });

    cout << "\n결과: " << pass_count << " passed, " << fail_count << " failed\n";
    return fail_count > 0 ? 1 : 0;
}
