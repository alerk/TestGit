#include <vector>

using namespace std;

#define ARRAY_LEADER_ERROR_NONE       -1
#define ARRAY_LEADER_ERROR_LENGTH     -2
#define ARRAY_LEADER_ERROR_DECREASING -3
#define ARRAY_LEADER_ERROR_OUTOFRANGE -4

#define LINKEDLIST_ERROR_NULLINPUT   -1
#define LINKEDLIST_ERROR_OUTOFRANGE  -2
#define LINKEDLIST_ERROR_HAS_A_CYCLE -3

#define DEEPEST_PIT_ERROR_NOPITS	       -1
#define DEEPEST_PIT_ERROR_ARRAY_OUTOFRANGE -1
#define DEEPEST_PIT_ERROR_VALUE_OUTOFRANGE -2
#define DEEPTEST_PIT_NO_DETECTED_POSITION  -1

/******************************************************************/
/*		    			1. BugfixingLeaderSorted				  */
/******************************************************************/

/* Return the leader of a array is the value that occurs in more
  than half of the elements of the array
  or a negative value which indicates an error
 */
int Array_GetLeader(vector<int> &array)
{
	size_t length = array.size();
	size_t index = 0;
	int leaderValue = -1;
	int noLeader = 0;

	if ((length < 1) || (length > 100000))
	{
		printf("The length of the array is invalid.");
		return ARRAY_LEADER_ERROR_LENGTH;
	}

	for (index = 0; index < length; ++index)
	{
		if ((array.at(index) < 0) && (array.at(index+1) > 2147483647))
		{
			printf("The value in the array is out of range [0 2147483647]");
			return ARRAY_LEADER_ERROR_OUTOFRANGE;
		}
		else if ((index < length-1) && (array.at(index) > array.at(index + 1)))
		{
			printf("The array isn't sorted in non-decreasing order");
			return ARRAY_LEADER_ERROR_DECREASING;
		}
		else if(array.at(index) == leaderValue)
		{
			noLeader++;
		}
		else if(noLeader < length/2)
		{
			noLeader = 1;
			leaderValue = array.at(index);
		}
	}

	if (noLeader > length / 2)
		return leaderValue;
	else
		return ARRAY_LEADER_ERROR_NONE;
};

/******************************************************************/
/*						2. PtrListLen							  */
/******************************************************************/
struct IntList
{
	int value;
	IntList *next;
};

/* Compute the length of single-linked list without a cycle
	return a negative value which indicates an error
*/
int SingleLink_GetLength(IntList * list)
{
	if (list == NULL) 
		return LINKEDLIST_ERROR_NULLINPUT;
	IntList *tmp = list;
	IntList *pCheckCycle = list;
	int length = 1;
	int iter = 0;
	while (true)
	{
		if(tmp->next == NULL)
		{
			break;
		}
		else
		{
			tmp = tmp->next;
			length++;
			//Check whether the linked list has a cycle
			for (iter = 1; iter < length - 1; ++iter)
			{
				if (tmp == pCheckCycle)
					return LINKEDLIST_ERROR_HAS_A_CYCLE;
				else
					pCheckCycle = pCheckCycle->next;
			}
			pCheckCycle = list;
		}
	}
	if (length > 5000)
		return LINKEDLIST_ERROR_OUTOFRANGE;
	return length;
}

/******************************************************************/
/*						3. DeepestPit							  */
/******************************************************************/

/* Return the maximum depth of a pit in a array
	or a negative value that indicates an error 
*/
int Array_GetDeepestPit(vector<int> &Array)
{
	int length = Array.size();
	if (length > 1000000) return DEEPEST_PIT_ERROR_ARRAY_OUTOFRANGE;
	if (length <= 2) return DEEPEST_PIT_ERROR_NOPITS;
	int p = 0;
	int q = DEEPTEST_PIT_NO_DETECTED_POSITION;
	int r = DEEPTEST_PIT_NO_DETECTED_POSITION;
	int localMaxDepth = 0;
	int maxDepth = 0;

	for (size_t i = 0; i < length-1; i++)
	{
		if ((Array.at(i) < -100000000) || (Array.at(i) > 100000000))
		{
			return DEEPEST_PIT_ERROR_ARRAY_OUTOFRANGE;
		}
		//Find q position
		if (q == DEEPTEST_PIT_NO_DETECTED_POSITION)
		{
			if (Array.at(i) < Array.at(i+1))
				q = i;
			else if(Array.at(i) == Array.at(i+1))
				p = i+1; //strictly decreasing
		}

		//Find r postion
		if ((q != DEEPTEST_PIT_NO_DETECTED_POSITION) && 
			(r == DEEPTEST_PIT_NO_DETECTED_POSITION))
		{
			if (Array.at(i) >= Array.at(i+1)) //strictly increasing
				r = i;
			else if (i + 1 == length - 1)
				r = i + 1;
			else 
				continue;
			localMaxDepth = (Array.at(p) - Array.at(q) > Array.at(r) - Array.at(q))
				? (Array.at(r) - Array.at(q)) : (Array.at(p) - Array.at(q));
			maxDepth = localMaxDepth > maxDepth ? localMaxDepth : maxDepth;
			p = r;
			i = r;
			q = DEEPTEST_PIT_NO_DETECTED_POSITION;
			r = DEEPTEST_PIT_NO_DETECTED_POSITION;
		}
	}
	return maxDepth > 0 ? maxDepth : -1;
}

void main()
{

}