#ifndef COMPUTE_GRADES_H
#define COMPUTE_GRADES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cmath>

using namespace std;

void error(string msg){
    cout << "Error: " << msg << endl;
}

class Student{
    string first_name;
    string last_name;
    vector<int> quiz;
    vector<int> hw;
    double quiz_ave;
    double hw_ave;
    double final_score;
    int course_score;
    string course_grade;
    static constexpr double quiz_weight = 0.4;
    static constexpr double hw_weight = 0.3;
    static constexpr double final_weight = 0.3;

public:
    Student () {
        this->first_name = "Missing";
        this->last_name = "Name";
        this->quiz = {};
        this->hw = {};
        this->final_score = 0;
        }

    void compute_grade(){
        if (quiz.size() == 0){
            quiz_ave = 0.0;
        }
        else if (quiz.size() == 1){
            quiz_ave = quiz[0];
        }
        else{
            auto min_score = *min_element(quiz.begin(), quiz.end());
            quiz_ave = (accumulate(quiz.begin(), quiz.end(), 0.0) - min_score) / (quiz.size() - 1);
        }

        if (hw.size() == 0){
            hw_ave = 0.0;
        }
        else{
            hw_ave = (accumulate(hw.begin(), hw.end(), 0.0)) / hw.size();
        }

        course_score = std::round((final_weight * final_score) + (hw_weight * hw_ave) + (quiz_weight * quiz_ave));

        if (course_score >= 97){
            course_grade = "A+";
        }
        else if (course_score >= 93){
            course_grade = "A";
        }
        else if (course_score >= 90){
            course_grade = "A-";
        }
        else if (course_score >= 87){
            course_grade = "B+";
        }
        else if (course_score >= 83){
            course_grade = "B";
        }
        else if (course_score >= 80){
            course_grade = "B-";
        }
        else if (course_score >= 77){
            course_grade = "C+";
        }
        else if (course_score >= 73){
            course_grade = "C";
        }
        else if (course_score >= 70){
            course_grade = "C-";
        }
        else if (course_score >= 67){
            course_grade = "D+";
        }
        else if (course_score >= 63){
            course_grade = "D";
        }
        else if (course_score >= 60){
            course_grade = "D-";
        }
        else{
            course_grade = "F";
        }
    };

    void read(istream & in){
        string line;
        // stringstream ss;
        // final_score = 0.0;
        while(getline(in, line) && !line.empty()){
            stringstream ss(line);
            string keyword;
            ss >> keyword;
            if (keyword == "Name"){
                ss >> first_name;
                ss >> last_name;
                for_each(istream_iterator<string>(ss), istream_iterator<string>(), [this](string name){
                    this->last_name += (" " + name);
                });
            }
            else if (keyword == "Quiz"){
                for_each(istream_iterator<int>(ss), istream_iterator<int>(), [this](int score){
                    if (score < 0 || score > 100){
                        error("invalid percentage " + to_string(score));
                        return;
                    }
                    quiz.push_back(score);
                });
            }
            else if (keyword == "HW"){
                for_each(istream_iterator<int>(ss), istream_iterator<int>(), [this](int score){
                    if (score < 0 || score > 100){
                        error("invalid percentage " + to_string(score));
                        return;
                    }
                    hw.push_back(score);
                });
            }
            else if (keyword == "Final"){
                int score;
                ss >> score;
                if (score < 0 || score > 100){
                    error("invalid percentage " + to_string(score));
                    return;
                }
                final_score = score;
            }
        }
    }

    void print(ostream & out) const{
        out << "Name\t" << first_name << " " << last_name << endl;
        out << "HW Ave:\t" << hw_ave << endl;
        out << "QZ Ave:\t" << quiz_ave << endl;
        out << "Final:\t" << final_score << endl;
        out << "Total:\t" << course_score << endl;
        out << "Grade:\t" << course_grade << endl;
    };

    string get_last_name(){
        return last_name;
    }

    string get_first_name(){
        return first_name;
    }

    friend ostream & operator << (ostream & out, const Student & student){
        student.print(out);
        return out;
    }

    friend istream & operator >> (istream & in, Student & student){
        student.read(in);
        return in;
    }
};

class Gradebook{
    vector<Student> students;

public:
    void compute_grades(){
        for_each(begin(students), end(students), [&](Student& s){
            s.compute_grade();
        });
    };
    void sort(){
        std::sort(begin(students), end(students), [](Student stu1, Student stu2){
            if (stu1.get_last_name() != stu2.get_last_name()){
                return stu1.get_last_name() < stu2.get_last_name();
            }
            else{
                return stu1.get_first_name() < stu2.get_first_name();
            }});
    };
    void print(ostream & out) const{
        for (const auto &s: students) {
            out << s << endl;
        }
    };
    void read(istream & in){
        Student student;

        while (in >> student) {
            students.push_back(student);
            student = Student();
        }
    };
    
    friend ostream & operator << (ostream & out, const Gradebook & gb){
        gb.print(out);
        return out;
    }

    friend istream & operator >> (istream & in, Gradebook & gb){
        gb.read(in);
        return in;
    }
};

int main(){
    ifstream in("gradebook.txt");
    Gradebook gb;
    in >> gb;
    gb.sort();
    gb.compute_grades();
    ofstream out("course_grades.txt");
    out << gb;
}

#endif