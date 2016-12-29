/*******************************************************************************
* Title                 :   Buggy
* Filename              :   buggy.h
* Author                :   Sladjan Kantar
* Origin Date           :   27/12/2016
* Notes                 :   None
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief init_buggy
 * - Function intialize all buggy 
 * @return
 */
void init_buggy();

/**
 * @brief break_buggy
 * - Stops buggy
 * @return
 */
void break_buggy();

/**
 * @brief start_buggy
 * - Starts buggy (forward)
 * @return
 */
void start_buggy();

/**
 * @brief forward
 * - Go forward
 * @return
 */
void forward();

/**
 * @brief backward
 * - Go backward
 * @return
 */
void backward();

/**
 * @brief right
 * - Turn right 90 degree
 * @return
 */
void right();

/**
 * @brief left
 * - Turn left 90 degree
 * @return
 */
void left();