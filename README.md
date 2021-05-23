I have done a lot of messing around with the settings, and have
listed below the best ones I have found from testing against the perfect
AI at https://connect4.gamesolver.org/?pos=44444432655225233322337777611111166776655

// AI SETTINGS
#define MAX_DEPTH 10 // 9 if your computer isn't beefy
#define HARDCODED_OPENINGS true
#define DEPTH_SCALING true
#define SCALING_FACTOR 0.18

// BOARD EVALUATION SETTINGS
#define TWO_WEIGHT 1
#define THREE_WEIGHT 5
#define BETTER_WEIGHT 3
#define BEST_WEIGHT 20 
