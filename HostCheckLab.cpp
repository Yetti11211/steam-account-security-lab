// Offline teaching example. No networking, credential input, or Steam integration.
// Inputs below are already-parsed, canonical ASCII hostnames, NOT arbitrary URLs.
#include <array>
#include <iostream>
#include <string_view>

bool badContainsBrand(std::string_view text) {
    return text.find("game") != std::string_view::npos;
}

bool matchesAllowedHost(std::string_view canonicalHost) {
    constexpr std::array<std::string_view, 2> allowed{
        "login.game.example", "help.game.example"
    };
    for (const auto host : allowed) {
        if (canonicalHost == host) return true;
    }
    return false;
}

struct Case {
    std::string_view value;
    bool expected;
};

int main() {
    constexpr std::array<Case, 5> cases{{
        {"login.game.example", true},
        {"login.game.example.other.invalid", false},
        {"help.game.example", true},
        {"other.invalid", false},
        {"game-gift.invalid", false}
    }};
    int failed = 0;
    for (const auto& test : cases) {
        const bool actual = matchesAllowedHost(test.value);
        std::cout << test.value
                  << " | substring=" << badContainsBrand(test.value)
                  << " | exact=" << actual << '\n';
        if (actual != test.expected) ++failed;
    }
    // This is an arbitrary URL, intentionally used ONLY with the bad check.
    constexpr std::string_view deceptivePath = "https://other.invalid/game";
    std::cout << deceptivePath << " | bad substring="
              << badContainsBrand(deceptivePath) << '\n';
    std::cout << "Failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
