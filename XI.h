/****************************************************************************/
/*                                                                          */
/* File Name : XI.h		                                                    */
/*                                                                          */
/****************************************************************************/


#ifndef XI_H_
#define XI_H_

//******************************************************************************
//----------------------------------<INCLUDE>-----------------------------------
//******************************************************************************

#include "AVLTree.h"
#include <cassert>


/**
 * class XI - Holding the values for the Xavier Institute.
 *
 * @param Students_	- an AVL tree holding the students sorted by their ID.
 * @param Aces_		- an AVL tree holding the students sorted by their power.
 * @param Teams_	- an AVL tree holding the teams sorted by their ID.
 */

//******************************************************************************
//----------------------------------<CLASS XI>----------------------------------
//******************************************************************************
class XI {

public:
//******************************************************************************
//------------------------------<XI :: XIEXCEPTION>-----------------------------
//******************************************************************************
	class XIException 		: public std::exception {};
	class StudentNotFound 	: public XIException {};
	class StudentAlreadyIn  : public XIException {};
	class TeamAlreadyIn		: public XIException {};
	class TeamNotFound 		: public XIException {};
	class TeamIsEmpty		: public XIException {};
	class InvalidID 		: public XIException {};
	class InvalidGrade 		: public XIException {};
	class InvalidPower 		: public XIException {};
	class NoStudentsInXI	: public XIException {};

//******************************************************************************
//-----------------------------<FORWARD DECLARATION>----------------------------
//******************************************************************************
	class Student;
	class Team;

//******************************************************************************
//------------------------------<XI :: COMPARE CLASS>---------------------------
//******************************************************************************

class CompareId{
	public:
		bool operator()(const Student&, const Student&) const;
		bool operator()(const Team&, const Team&) const;
	};

class ComparePower{
	public:
		bool operator()(const Student&, const Student&) const;
	};

//******************************************************************************
//---------------------------------<XI :: Student>------------------------------
//******************************************************************************
class Student{
public:

	//-------------------<STUDENT :: EXCEPTION>------------------

	class StudentException 		: public std::exception {};
	class InvalidID 			: public StudentException {};
	class InvalidGrade 			: public StudentException {};
	class InvalidPower 			: public StudentException {};
	class NoTeamAssigned 		: public StudentException {};
	class NoSuchTeam			: public StudentException {};

	//-----------------------<CONSTRUCTOR>-----------------------

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
	Student(int id, int grade, int power);

	//---------------------<CLASS FUNCTIONS>---------------------

	/**
	 * Id: Returns the id of the calling student (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  The id of the calling student (this).
	 */
	int Id() const;

	/**
	 * Grade: Returns the grade of the calling student (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  The grade of the calling student (this).
	 */
	int Grade() const;


	/**
	 * Power: Returns the power of the calling student (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  The power of the calling student (this).
	 */
	int Power() const;


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
	void IncreasePower(int power);

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
	XI::Team* Team() const;

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
	void SetTeam(XI::Team* team);

private:

	//-----------------------<MEMBER TYPES>----------------------

	int id_;
	int grade_;
	int power_;
	XI::Team* team_;
};


//******************************************************************************
//----------------------------------<XI :: Team>--------------------------------
//******************************************************************************

class Team{
public:

	//--------------------<TEAM :: EXCEPTION>--------------------

	class TeamException 			: public std::exception {};
	class InvalidID		 			: public TeamException {};
	class TeamIsEmpty				: public TeamException {};
	class StudentNotFound			: public TeamException {};
	class StudentAlreadyAssigned	: public TeamException {};

	//-----------------------<CONSTRUCTOR>-----------------------

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
	Team(int id);

	//---------------------<CLASS FUNCTIONS>---------------------

	/**
	 * Id: Returns the id of the calling Team (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  The id of the calling Team (this).
	 */
	int Id() const;

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
	void AddStudent(const Student& student);

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
	void RemoveStudent(const Student& student);


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
	const Student& FindStudent(const Student& student) const;

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
	const Student& GetMostPowerfull()const;

	/**
	 * GetAllStudents: returns array of all students sorted by their power.
	 *
	 * @complexity O(n). n is number of the students.
	 *
	 * @return
	 *  array of all students sorted by ID.
	 *  if the team is empty throw a 'TeamIsEmpty' exeption.
	 */
	const Student** GetAllStudents()const;

	int Size() const;

private:

	//-----------------------<MEMBER TYPES>----------------------

	int id_;
	AVLTree<Student,ComparePower> students_;

};

//******************************************************************************
//----------------------------------<CONSTRUCTOR>-------------------------------
//******************************************************************************

/**
 * XI: creates a new empty XI.
 *
 * @complexity O(1).
 *
 * @return
 * 	a new empty XI.
 */
XI ();

//******************************************************************************
//----------------------------------<DESTRUCTOR>--------------------------------
//******************************************************************************

/**
 * ~XI: deallocates the calling XI (this).
 */
~XI();

//******************************************************************************
//-------------------------------<CLASS FUNCTIONS>------------------------------
//******************************************************************************

/**
 * addStudent: adds a student with the given parameters to the calling XI (this).
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
void addStudent(int id, int grade, int power);

/**
 * AddTeam: adds a team with the given id to the calling XI (this).
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
void AddTeam(int id);

/**
 * MoveStudentToTeam: moves the student with the given id to the team with the
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
void MoveStudentToTeam(int studentId, int teamId);

/**
 * GetMostPowerfull: returns the most powerfull student on the team with the
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
 *
 */
const Student& GetMostPowerfull(int teamId)const;

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
void RemoveStudent(int id);

/**
 * GetAllStudentsByPower: returns an array of the students on the team with the
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
 */
const Student** GetAllStudentsByPower(int teamId, int *size)const;

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
void IncreaseLevel(int grade, int power);

/**
 * Ace: Returns the mostpowerfull student in the calling XI (this).
 */
const Student& Ace()const;

/**
 * Size: Returns the number of students in the calling XI (this).
 */
int Size()const;

private:
//******************************************************************************
//---------------------------------<MEMBER TYPES>-------------------------------
//******************************************************************************

AVLTree<Student,CompareId> Students_;
AVLTree<Student,ComparePower> Aces_;
AVLTree<Team,CompareId> Teams_;

};
















#endif /* XI_H_ */
