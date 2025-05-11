# cpp-assign
A C++20 helper analogous to structured bindings to transparently assign values from pairs and tuples to already existing variables

Example:

    std::tuple<int, float, std::string> create_tuple();
    
    int a;
    float b;
    std::string c;

    assign(a,b,c) = create_tuple();

## Rationale

this assign helper fills a gap in the Standard. Structured bindings creates new variables, while std::tie is non-intuitively named and is a C++11 construct that have limited support for rvalues and move syntax. This assign helper leverages concepts and C++20 features to provide a lightweight and intuitive method of assigning from std::pair:s and std::tuple:s that respects recent language features.

## Comparisons to structured bindings

## Comparison to std::tie 
