#ifndef Participant_H
#define Participant_H

#include <iostream>
#include <cstdlib>

class Participant
{
public:
    int id;
    int solved;
    int time;
    int score;
    int attempts;

    
    Participant()
    {
        id = rand() % 1000;
        solved = rand() % 6;
        time = 60 + rand() % 241;
        score = rand() % 26;
        attempts = rand() % 21;
    }

    
    bool operator<(const Participant& other) const
    {
        if (score != other.score) return score > other.score;
        if (solved != other.solved) return solved > other.solved;
        if (time != other.time) return time < other.time;
        if (attempts != other.attempts) return attempts < other.attempts;
        return id < other.id;
    }


    bool operator>(const Participant& other) const
    {
        if (score != other.score) return score < other.score;
        if (solved != other.solved) return solved < other.solved;
        if (time != other.time) return time > other.time;
        if (attempts != other.attempts) return attempts > other.attempts;
        return id > other.id;
    }

    friend std::ostream& operator<<(std::ostream& out, const Participant& c)
    {
        out << c.id << "\t"
            << c.score << "\t"
            << c.solved << "\t"
            << c.time << "\t"
            << c.attempts;
        return out;
    }

   
    static void printHeader()
    {
        std::cout << "ID\tScore\tSolved\tTime\tAttempts\n";
    }
};

#endif