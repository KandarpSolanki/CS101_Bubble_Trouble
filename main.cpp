#include <sstream>
#include "shooter.h"
#include "bubble.h"

// 17.49285568

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);


void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        // Check for all bullets if going out of frame
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i); // Destroy the bullet which is out of the game's frame
        }
    }
}

void create_bubbles_small(vector<Bubble> &bubbles, double x_pos, double y_pos, double radius, int lev_num){
    Color bub_color = COLOR(100+50*lev_num, 255-40*lev_num, 225 - 10*lev_num); ///Creating random colored bubbles with 'Color' datatype
    bubbles.push_back(Bubble(x_pos, y_pos, radius/2, -BUBBLE_DEFAULT_VX-50*(3*lev_num+1), 100, bub_color));
    bubbles.push_back(Bubble(x_pos, y_pos, radius/2, BUBBLE_DEFAULT_VX+50*(3*lev_num+1), 100, bub_color));

}


int collide_bullets_bubbles(vector<Bullet> &bullets,vector<Bubble> &bubbles, int &score, int lev_num){
    // collision of bullets
    for(unsigned int i = 0; i < bullets.size(); i++){
        for (unsigned int j = 0; j < bubbles.size(); j++){
            // Check for every bubble-bullet pair using nested for loop
            if (pow((bullets[i].get_center_x() - bubbles[j].get_center_x()),2) + pow((bullets[i].get_center_y() - bubbles[j].get_center_y()),2) < pow((5*1.414 + bubbles[j].get_radius()),2)){ // Using pythagoras for the maximum distance they can collide i.e x^2 + y^2 = (5sqrt(2) + 10)^2 = 17.07106^2 = 291.421
                //bullets.erase(bullets.begin()+i); //removed the condition of bullet disappear so that it does not generate an error of colliding two bubbles simultaneously
                if (bubbles[j].get_radius() > BUBBLE_RADIUS_THRESHOLD){
                    score++; //Increment global score
                    create_bubbles_small(bubbles, bubbles[j].get_center_x(), bubbles[j].get_center_y(), bubbles[j].get_radius(), lev_num);  // Create smaller bubbles when it collide
                    bubbles.erase(bubbles.begin()+j);  // Erase/Disappear the jth bubble which was collided
                    bullets.erase(bullets.begin()+i);  // Erase/Disappear the ith bullet which was collided
                    return 0;
                }
                else{
                    score++; //Increase score if bullet-bubble collide
                    bubbles.erase(bubbles.begin()+j);  // Erase/Disappear the jth bubble which was collided
                    bullets.erase(bullets.begin()+i);  // Erase/Disappear the ith bullet which was collided
                    return 0;
                }
            }
        }
    }
}



void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME); //Move ahead the bubble with step_time
    }
}


vector<Bubble> create_bubbles(int lev_num)
{
    vector<Bubble> bubbles; //Creation of a vector containing all the bubbles at new level
    Color bub_color = COLOR(100+50*lev_num, 255-40*lev_num, 225 - 10*lev_num); ///Creating random colored bubbles with 'Color' datatype
    // create initial bubbles in the game
    int j = 1; //for randomisation
    for (int i = 1; i<lev_num + 2; i++){
        // Create bubbles depending on level of the game
        bubbles.push_back(Bubble(WINDOW_X/2.0 - 30*i*j, BUBBLE_START_Y + 20*i, BUBBLE_DEFAULT_RADIUS*lev_num, -j*BUBBLE_DEFAULT_VX-50*j*(3*lev_num+1), -100, bub_color));
        //bubbles.push_back(Bubble(WINDOW_X/4.0 + 20*i*-j, BUBBLE_START_Y + 30*i, BUBBLE_DEFAULT_RADIUS*lev_num, BUBBLE_DEFAULT_VX+50*(3*i-1), 0, bub_color));
        j *= -1;
    }
    return bubbles; // return the vector bubbles containing all the circles i.e bubbles
    
}


bool shooter_dead(vector<Bubble> &bubbles, Shooter &shooter){
    for (unsigned int j=0; j < bubbles.size(); j++){
        // Check for the maximum range in which it can exist within the head or body of the shooter 
        if((pow((shooter.get_head_center_x() - bubbles[j].get_center_x()),2) + pow((shooter.get_head_center_y() - bubbles[j].get_center_y()),2) < pow(17.49 + bubbles[j].get_radius(),2)) || (pow((shooter.get_body_center_x() - bubbles[j].get_center_x()),2) + pow((shooter.get_body_center_y() - bubbles[j].get_center_y()),2) < pow(17.49 + bubbles[j].get_radius(),2))){ //17.49 = sqrt(306) = sqrt(15^2 + 9^2) - Length of center of body to circle's circumference
            //cout << "Hurray!" << endl; //Debug Purpose
            //health--; //If hits health goes down!
            //Shooter shooter(shooter.get_body_center_x(), shooter.get_body_center_x(), SHOOTER_VX,30,18,8,COLOR(255, 0, 0));
            //wait(2);
            //bubbles.clear(); //Clear all the bubbles
            //bubbles = create_bubbles(level); //Reset that level while not changing the timer
            return true; //Return True so as to check conditions in the 'while' loop of the 'main game loop' 
        }
    }
    return false; //Return false if not within the range of collision
}

int main()
{
    //Canvas Initialisation
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    std::stringstream temp;
    std::string temp2;
    // Definition Timer, Level, Health, Score Variables
    float timer = 25000;
    int level_num = 1;
    int health_left = 5;
    int score = 0;

    // Blue bottom line
    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    Line b2(0, 40, WINDOW_X, 40);
    b2.setColor(COLOR(0, 0, 255));
    
    // Command entered by user text 'Cmd: '
    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    // Text for Level Counter
    temp.clear();
    temp << level_num;
    temp >> temp2;
    std:: string lev = "Level: "+temp2;
    Text level(LEFT_MARGIN+370, TOP_MARGIN, lev);

    // Text for 'Timer' on screen
    temp.clear();
    temp << int(timer/1000);
    temp >> temp2;
    std::string timerstr = "Time left: "+temp2+" s";
    Text timertext(LEFT_MARGIN+330, BOTTOM_MARGIN, timerstr);

    // Text for Score counter
    temp.clear();
    temp << score;
    temp >> temp2;
    std:: string scorestr = "Score: "+temp2;
    Text scoretext(LEFT_MARGIN+150, BOTTOM_MARGIN, scorestr);
    
    // Text for NEW LEVEL
    temp.clear();
    temp << level_num;
    temp >> temp2;
    std:: string newlev = "Level "+temp2+"!";
    Text newlevtext(LEFT_MARGIN+170, BOTTOM_MARGIN-250, newlev);


    // Health counter
    temp.clear();
    temp << health_left;
    temp >> temp2;
    std:: string health_str = "Health Left: "+temp2;
    Text health(LEFT_MARGIN+20, TOP_MARGIN, health_str);
    

    wait(2); //Wait to read
    newlevtext.setMessage(""); //Disappear pop-up
    
    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles(level_num);

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;

    
    // Main game loop
    while (timer > 0 && (health_left>0)) //Check whether time is there & if both health & time is zero disallow to enter loop
    {
        bool check_before = shooter_dead(bubbles, shooter);

        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {   
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);


            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true, shooter_dead(bubbles, shooter));
            else if(c == 'd')
                shooter.move(STEP_TIME, false, shooter_dead(bubbles, shooter));
            else if(c == 'w' && bullets.size() < 5) // Allow only 5 bullets on screen to maintain interactive frame rate
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        //int x = timer/1000;
        //string y = to_string(x);
        //cout << y << endl;
        //timeint.setMessage(y);
        shooter.move(0, true, shooter_dead(bubbles, shooter)); 

        temp.clear();
        temp << int(timer/1000);
        temp >> temp2;
        timertext.setMessage("Time left: "+temp2+" s");
        timer -= 50+level_num*15; //To match the timer speed because no. of iterations increase and hence time lag may increases

        temp.clear();
        temp << health_left;
        temp >> temp2;
        health.setMessage("Health Left: "+temp2); //Update health left status

        temp.clear();
        temp << score;
        temp >> temp2;
        scoretext.setMessage("Score: "+temp2); //Update Score status


        if (bubbles.size() == 0){
            bullets.clear(); //clear all bullets of previous level
            level_num += 1; //Increase level
            temp.clear();
            temp << level_num;
            temp >> temp2;
            newlevtext.setMessage("Level "+temp2+"!"); //Pop-up for NEW LEVEL
            level.setMessage("Level: "+temp2); //Update the level no. on screen
            wait(2); //Wait to read Pop-up
            newlevtext.setMessage(""); //Disappear pop-up
            bubbles = create_bubbles(level_num); //Initialise next level bubbles (harder level) depending on Level No.
            timer = 25000+level_num*15000; //Reset timer to 15 secs * level no. because more bubbles so more time
        }

        
        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        //Check collision of bullets & updation of score (if collide)
        collide_bullets_bubbles(bullets, bubbles, score, level_num);

        bool check_after = shooter_dead(bubbles, shooter);

        if (check_before == false && check_after == true){
            health_left--;
        }

        wait(STEP_TIME); //wait time to maintain frame rate 
    }

    // Update the bubbles
    move_bubbles(bubbles);

    // Game Over Message
    temp.clear();
    temp << int(timer/1000);
    temp >> temp2;
    timertext.setMessage("Time left: "+temp2+"s"); //Timer end message
    
    temp.clear();
    temp << health_left;
    temp >> temp2;
    health.setMessage("Health Left: "+temp2); //Zero health message
 
    Text gameo(250, 240, ""); // Initialise 'gameo'

    if (health_left == 0){
        gameo.setMessage("You ran out of lifes!"); //Print health over
    }
    if (timer < 0){
        gameo.setMessage("Time's up!");  // Print time over
    }
    wait(3);
    gameo.setMessage("GAME OVER!");  //Pop up of Game over
    wait(2);
    gameo.setMessage("Click to exit.");
    getClick(); //Click to exit canvas
}
