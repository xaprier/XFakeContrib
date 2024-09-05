#ifndef GITHUBCONTRIBLEVELS_HPP
#define GITHUBCONTRIBLEVELS_HPP

#include <map>
#include <string>

enum GithubContribLevels {
    NONE,
    FIRST_QUARTILE,
    SECOND_QUARTILE,
    THIRD_QUARTILE,
    FOURTH_QUARTILE
};

static std::map<std::string, GithubContribLevels> GitHubContribLevels{
    {"NONE", GithubContribLevels::NONE},
    {"FIRST_QUARTILE", GithubContribLevels::FIRST_QUARTILE},
    {"SECOND_QUARTILE", GithubContribLevels::SECOND_QUARTILE},
    {"THIRD_QUARTILE", GithubContribLevels::THIRD_QUARTILE},
    {"FOURTH_QUARTILE", GithubContribLevels::FOURTH_QUARTILE},
};

#endif  // GITHUBCONTRIBLEVELS_HPP