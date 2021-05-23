I have done a lot of messing around with the settings, and have
listed below the best ones I have found from testing against the perfect
AI at https://connect4.gamesolver.org/?pos=44444432655225233322337777611111166776655

// AI SETTINGS
#define ACTIVE_AI true
#define MAX_DEPTH 10 // (9 if you want faster runtimes)
#define HARDCODED_OPENINGS true
#define DEPTH_SCALING true
#define SCALING_FACTOR 0.18

// BOARD EVALUATION SETTINGS
#define TWO_WEIGHT 1 // probably best to keep this very low...
#define THREE_WEIGHT 5 // 4 or 5 is best(?)
#define BETTER_WEIGHT 3 // not even gonna pretend to know how to set this (if at all), just keep it lower than the one below it
#define BEST_WEIGHT 20 // keep this very high (it happens rarely and almost always results in a win)
