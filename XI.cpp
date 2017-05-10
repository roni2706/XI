/****************************************************************************/
/*                                                                          */
/* File Name : XI.cpp	                                                    */
/*                                                                          */
/****************************************************************************/


//******************************************************************************
//----------------------------------<INCLUDE>-----------------------------------
//******************************************************************************

#include "XI.h"


//******************************************************************************
//------------------------------<XI :: COMPARE CLASS>---------------------------
//******************************************************************************
bool XI::CompareId::operator ()(const Student& s1, const Student& s2) const{
	if(s1.Id()<s2.Id()){
			return true;
		}
		return false;
}

bool XI::CompareId::operator ()(const Team& t1, const Team& t2) const{
	if(t1.Id()<t2.Id()){
			return true;
		}
		return false;
}

bool XI::ComparePower::operator ()(const Student& s1, const Student& s2) const{
	if(s1.Power()<s2.Power()){
		return true;
	}
	else if(s1.Power()==s2.Power()){
		if(s1.Id()<s2.Id()){
			return true;
		}
	}
	return false;
}

//******************************************************************************
//---------------------------------<XI :: Student>------------------------------
//******************************************************************************

//---------------------------------<CONSTRUCTOR>--------------------------------

/**
 * Student: Creates a new student with the given parameter.
 *
 * @complexity O(1).
 *
 * @param id 	- the given id for new student.
 * @param grade - the given grade for new student.
 * @param power - the given power for a new student.
 *
 * @return
 * 	a new student with the given parameters.
 *
 * 	if id is invalid, throw an 'InvalidID' exeption.
 * 	if grade is invalid, throw an 'InvalidGrade' exeption.
 * 	if power is invalid, throw an 'InvalidPower exeption.
 */
XI::Student::Student(int id, int grade, int power):
		id_(id),grade_(grade),power_(power),team_(NULL){}

//-------------------------------<CLASS FUNCTIONS>------------------------------

/**
 * Id: Returns the id of the calling student (this).
 *
 * @complexity O(1).
 *
 * @return
 *  The id of the calling student (this).
 */
int XI::Student::Id() const{
	return id_;
}

/**
 * Grade: Returns the grade of the calling student (this).
 *
 * @complexity O(1).
 *
 * @return
 *  The grade of the calling student (this).
 */
int XI::Student::Grade() const{
	return grade_;
}

/**
 * Power: Returns the power of the calling student (this).
 *
 * @complexity O(1).
 *
 * @return
 *  The power of the calling student (this).
 */
int XI::Student::Power() const{
	return power_;
}

/**
 * IncreasePower: increase the power of the calling student (this) by the
 * given amount.
 *
 * @param power - the given amount.
 *
 * @complexity O(1).
 *
 * @return
 *  if the power is invalid, throw an 'InvalidPower exeption.
 */
void XI::Student::IncreasePower(int power){
	if(power<=0){
		throw InvalidPower();
	}
	power_+=power;
}

/**
 * Team: Returns a pointer to the team of the calling student (this).
 *
 * @complexity O(1).
 *
 * @return
 *  A pointer to the team of the calling student (this).
 *
 *  if the student is not assinged to a team throw a 'NoTeamAssigned'
 *  exeption.
 */
XI::Team* XI::Student::Team() const{
	if(!team_){
		throw NoTeamAssigned();
	}
	return team_;
}

/**
 * SetTeam: Sets the team of the calling student (this) to the given team.
 *
 * @complexity O(1).
 *
 * @param team - the given team to set.
 *
 * @return
 *  nothing.
 */
void XI::Student::SetTeam(XI::Team* team){
	team_=team;
}


//******************************************************************************
//----------------------------------<XI :: Team>--------------------------------
//******************************************************************************

//---------------------------------<CONSTRUCTOR>--------------------------------

/**
 * Team: Creates a new Tean with the given parameters.
 *
 * @complexity O(1).
 *
 * @param id - the given id for new Team.
 *
 * @return
 * 	a new team with the given parameters.
 * 	if the id is invalid, throw an 'InvalidID' exeption
 */
XI::Team::Team(int id):id_(id),students_(){
}

//-------------------------------<CLASS FUNCTIONS>------------------------------

/**
 * Id: Returns the id of the calling Team (this).
 *
 * @complexity O(1).
 *
 * @return
 *  The id of the calling Team (this).
 */
int XI::Team::Id() const{
	return id_;
}

/**
 * AddStudent: add a given student to the calling team (this).
 *
 * @complexity O(log(n)). n is the number of students in the team.
 *
 * @param student - the given student to add.
 *
 * @return
 *  if the given student is already on the team throw a
 *  'StudentAlreadyAssigned' exeption.
 */
void XI::Team::AddStudent(const Student& student){
	try{
		students_.insert(student);
	}
	catch(Tree<Student,ComparePower>::alredyInTree&){
		throw StudentAlreadyAssigned();
	}
}

/**
 * RemoveStudent: removes a given student from the calling team (this).
 *
 * @complexity O(log(n) => n is the number of students in the team).
 *
 * @param student - the given student to remove.
 *
 * @return
 *  if the given student is not on the team throw a 'StudentNotFound'
 *  exeption.
 */
void XI::Team::RemoveStudent(const Student& student){
	try{
		students_.erase(student);
	}
	catch(Tree<Student,ComparePower>::notFoundInTree&){
		throw StudentNotFound();
	}
}

/**
 * FindStudent: Finds a given student on the calling team (this).
 *
 * @complexity O(log(n) => n is the number of students in the team).
 *
 * @param student - the given student to find.
 *
 * @return
 *  the given student from the team.
 *
 *  if the given student is not on the team throw a 'StudentNotFound'
 *  exeption.
 */
const XI::Student& XI::Team::FindStudent(const Student& student) const{
	try{
		students_.at(student);
	}
	catch(Tree<Student,ComparePower>::notFoundInTree&){
		throw StudentNotFound();
	}
	return student;
}

/**
 * GetMostPowerfull: returns the most powerfull student on the calling team
 * (this).
 *
 * @complexity O(1).
 *
 * @return
 *  The most powerfull student on the calling team (this).
 *
 *  if the team is empty throw a 'TeamIsEmpty' exeption.
 */
const XI::Student& XI::Team::GetMostPowerfull()const{
	if(students_.empty()){
		throw TeamIsEmpty();
	}
	return students_.max();
}

/**
 * GetAllStudents: returns array of all students sorted by their power.
 *
 * @complexity O(n). n is number of the students.
 *
 * @return
 *  array of all students sorted by ID.
 *  if the team is empty throw a 'TeamIsEmpty' exeption.
 */
const XI::Student** XI::Team::GetAllStudents()const{
	if(students_.empty()){
		throw TeamIsEmpty();
	}
	return students_.toArray();
}

//******************************************************************************
//----------------------------------<CLASS XI>----------------------------------
//******************************************************************************

//******************************************************************************
//----------------------------------<CONSTRUCTOR>-------------------------------
//******************************************************************************

/**
 * XI: Creates a new empty XI.
 *
 * @complexity O(1).
 *
 * @return
 * 	a new empty XI.
 */
XI::XI ():Students_(),Aces_(),Teams_(){}

//******************************************************************************
//----------------------------------<DESTRUCTOR>--------------------------------
//******************************************************************************

/**
 * ~XI: Deallocates the calling XI (this).
 */
XI::~XI(){
	const XI::Student** students=Students_.toArray();
	for(int i=0;i<Students_.size();i++){
	   delete students[i];
	}
	delete[] students;
	const XI::Team** teams=Teams_.toArray();
	for(int i=0;i<Teams_.size();i++){
		   delete teams[i];
		}
	delete[] teams;
}

//******************************************************************************
//-------------------------------<CLASS FUNCTIONS>------------------------------
//******************************************************************************

/**
 * addStudent: Adds a student with the given parameters to the calling XI (this).
 *
 * @complexity O(log(n)). n is number of students held by the XI.
 *
 * @param id 	- the given id.
 * @param grade - the given grade.
 * @param power - the given power.
 *
 * @return
 *  True if a student with the same id was not already held by the XI,
 *  or false otherwise.
 *
 * 	if the id is invalid, throw an 'InvalidID' exeption.
 * 	if grade is invalid, throw an 'InvalidGrade' exeption.
 * 	if power is invalid, throw an 'InvalidPower exeption.
 * 	if a student with the given id already exists throw a 'StudentAlreadyIn'
 * 	exeption.
 */
void XI::addStudent(int id, int grade, int power){
	if(id <=0){
		throw InvalidID();
	}
	if(grade<0){
		throw InvalidGrade();
	}
	if(power<=0){
		throw InvalidPower();
	}
	XI::Student* student=new Student(id,grade,power);
	try{
		Students_.insert(*(student));
		Aces_.insert(*(student));
	}
	catch(Tree<Student,CompareId>::alredyInTree&){
		throw StudentAlreadyIn();
	}
}

/**
 * AddTeam: Adds a team with the given id to the calling XI (this).
 *
 * @complexity O(log(k)). k is number of teams held by the XI.
 *
 * @param id - the given id.
 *
 * @return
 *  True if a team  with the same id was not already held by the XI,
 *  or false otherwise.
 *
 * 	if the id is invalid, throw an 'InvalidID' exeption.
 * 	if a team with the given id already exists throw a 'TeamAlreadyIn' exeption.
 */
void XI::AddTeam(int id){
	if(id<=0){
		throw InvalidID();
	}
	XI::Team* team=new Team(id);
	try{
		Teams_.insert(*(team));
	}
	catch(XI::Team::InvalidID&){
		delete team;
		throw InvalidID();
	}
	catch(Tree<Team,CompareId>::alredyInTree&){
		throw TeamAlreadyIn();
	}
}

/**
 * MoveStudentToTeam: Moves the student with the given id to the team with the
 * given id.
 *
 * @complexity O(log(k)+log(n)). n is the number of students held by the XI.
 * 								 k is number of teams held by the XI.
 *
 * @param studentId - the id of the student.
 * @param teamId	- the id of the team.
 *
 * @return
 *  True if a student with the given id was not already in the team with the
 *  given id, or false otherwise.
 *
 * 	if the id is invalid, throw an 'InvalidID' exeption.
 *  if a student with the given id is not in the calling XI, throw
 *  'StudentNotFound' exeption.
 *  if a team with the given id is not in the calling XI, throw 'TeamNotFound'
 *  exeption.
 */
void XI::MoveStudentToTeam(int studentId, int teamId){
	if(teamId<=0 || studentId<=0){
		throw InvalidID();
	}
	Student* student;
	Team* team;
	try{
		student=&(const_cast<Student&>(Students_.at(Student(studentId,0,0))));
		team=&(const_cast<Team&>(Teams_.at(Team(teamId))));
	}
	catch(Tree<Student,CompareId>::notFoundInTree&){
		throw StudentNotFound();
	}
	catch(Tree<Team,CompareId>::notFoundInTree&){
		throw TeamNotFound();
	}
	try{
		if(student->Team()->Id()==teamId){
			return;
		}
		student->Team()->RemoveStudent(*student);
	}
	catch(XI::Student::NoTeamAssigned&){
		//All good
	}
	catch(XI::Team::StudentNotFound&){
		//Very very bad
	}
	try{
		team->AddStudent(*student);
		student->SetTeam(team);
	}
	catch(XI::Team::StudentAlreadyAssigned&){
		//Very very bad
	}
}

/**
 * GetMostPowerfull: Returns the most powerfull student on the team with the
 * given id. If the id is negative returns the most powerfull student on the
 * calling XI (this).
 *
 * @complexity O(log(k)). k is the number of teams held by the XI.
 * @complexity O(1).
 *
 * @param teamId - the id of the team.
 *
 * @return
 *  the most powerfull student on the team with the given id.
 *
 *  if the id is invalid, throw an 'InvalidID' exeption
 *  if a team with the given id is not in the calling XI, throw 'TeamNotFound'.
 *  if the team is empty throw a 'TeamIsEmpty' exeption.
 *  if there are no students in the XI throw a 'NoStudentsInXI' exeption.
 *
 */
const XI::Student& XI::GetMostPowerfull(int teamId)const{
	if(teamId==0){
		throw InvalidID();
	}
	try{
		if(teamId<0){
			return Ace();
		}
	}
	catch(XI::NoStudentsInXI&){
		throw NoStudentsInXI();
	}
	Team* team;
	try{
		team=&(const_cast<Team&>(Teams_.at(Team(teamId))));
	}
	catch(Tree<Team,CompareId>::notFoundInTree&){
		throw TeamNotFound();
	}
	try{
		return team->GetMostPowerfull();
	}
	catch(XI::Team::TeamIsEmpty&){
		throw TeamIsEmpty();
	}
}

/**
 * RemoveStudent: Removes a student with the given id from the calling XI (this).
 *
 * @complexity O(log(n)). n is the number of students held by the XI.
 *
 * @param id - the given id.
 *
 * @reutrn
 *  True if a student with the given id was found on the calling XI (this).
 *
 *  if the id is invalid, throw an 'InvalidID' exeption.
 */
void XI::RemoveStudent(int id){
	if(id<=0){
		throw InvalidID();
	}
	Student* student;
	Team* team;
	try{
		student=&(const_cast<Student&>(Students_.at(Student(id,0,0))));
		team=&(const_cast<Team&>(Teams_.at(*(student->Team()))));
		Students_.erase(*student);
		Aces_.erase(*student);
		team->RemoveStudent(*student);
	}
	catch(Tree<Student,CompareId>::notFoundInTree&){
		throw StudentNotFound();
	}
	catch(XI::Student::NoTeamAssigned&){
		//All good
	}
	catch(Tree<Team,CompareId>::notFoundInTree&){
		//Very very bad
	}
	catch(XI::Team::StudentNotFound&){
		//Very very bad
	}
	delete student;
}

/**
 * GetAllStudentsByPower: Returns an array of the students on the team with the
 * given id, sorted by their power. if the id is negative returns an array of
 * all the students on XI, sorted by their power.
 *
 * @complexity O(n). n is the number of students held by the XI.
 * @complexity O(n+log(k)). n is the number of students on the team.
 * 							k is the number of teams held by the calling XI.
 *
 * @param teamId - the given id.
 *
 * @return
 *  an array of the students sorted by thier power.
 *
 *  if the id is invalid, throw an 'InvalidID' exeption.
 *  if a team with the given id is not in the calling XI, throw 'TeamNotFound'.
 *  if the team is empty throw a 'TeamIsEmpty' exeption.
 *  if there are no students in the XI throw a 'NoStudentsInXI' exeption.
 */
const XI::Student** XI::GetAllStudentsByPower(int teamId)const{
	if(teamId==0){
		throw InvalidID();
	}
	if(teamId<0){
		if (Students_.empty()){
			throw NoStudentsInXI();
		}
		return Aces_.toArray();
	}
	Team* team;
	try{
		team=&(const_cast<Team&>(Teams_.at(Team(teamId))));
	}
	catch(Tree<Team,CompareId>::notFoundInTree&){
		throw TeamNotFound();
	}
	try{
		return team->GetAllStudents();
	}
	catch(XI::Team::TeamIsEmpty&){
		throw TeamIsEmpty();
	}
}

/**
 * IncreaseLevel: Increases the power of all the students in the given grade by
 * the given amount.
 *
 * @complexity O(n). n is the number of students held by the XI.
 *
 * @param grade - the given grade.
 * @param power - the given power to increase.
 *
 * @return
 *  True if the power of the students were increased, or false otherwise.
 *
 * 	if grade is invalid, throw an 'InvalidGrade' exeption.
 * 	if power is invalid, throw an 'InvalidPower exeption.
 */
void XI::IncreaseLevel(int grade, int power){
	if(grade<0){
		throw InvalidGrade();
	}
	if(power<=0){
		throw InvalidPower();
	}
	const XI::Student** students=Students_.toArray();
	for(int i=0;i<Students_.size();i++){
		if(students[i]->Grade()==grade){
			(const_cast<Student&>(*(students[i]))).IncreasePower(power);
		}
	}
	delete[] students;
}

/**
 * Ace: Returns the mostpowerfull student in the calling XI (this).
 */
const XI::Student& XI::Ace()const{
	if (Students_.empty()){
		throw NoStudentsInXI();
	}
	return Aces_.max();
}

/**
 * Size: Returns the number of students in the calling XI (this).
 */
int XI::Size()const{
	return Students_.size();
}












