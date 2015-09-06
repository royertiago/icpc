#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    /* To avoid problems with floating-point numbers,
     * we will multiply everything by 10,
     * thus effectively working with pemilles instead of percent.
     */
    map< string, int > permille;
    int parties, guesses;
    cin >> parties >> guesses;
    for( int i = 0; i < parties; i++ ) {
        string party;
        int a, b; // decimal and fractionary parts
        char decimal_separator; // ignored
        cin >> party >> a >> decimal_separator >> b;
        permille[party] = 10*a + b;
    }
    for( int i = 1; i <= guesses; i++ ) {
        /* We will parse each query two tokens at time.
         * While the second token is a "+",
         * we will interpret the first token as a party name
         * and add its permille to the sum.
         * When the second token is not a "+",
         * then the token must be a comparison operator
         * and the next value is the number with which we compare.
         *
         * By using a do-while loop,
         * we ensure the last party (which is followed by
         * a comparison operator istead of a "+")
         * is also added to the sum.
         */
        string party, op;
        int sum = 0;
        do {
            cin >> party >> op;
            sum += permille[party];
        } while( op == "+" );

        int guess;
        cin >> guess;
        guess *= 10;

        bool right; // If the guess was right
        if( op == "<" )
            right = sum < guess;
        if( op == ">" )
            right = sum > guess;
        if( op == "=" )
            right = sum == guess;
        if( op == "<=" )
            right = sum <= guess;
        if( op == ">=" )
            right = sum >= guess;

        cout << "Guess #" << i
             << (right ? " was correct.\n" : " was incorrect.\n");
    }
    return 0;
}
