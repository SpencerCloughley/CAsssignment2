#include <vector>

using namespace std;

class Ticket {
private:
	int ticketId;
	vector<int> lineNumbers;
public:
	int getTicketId() {
		return ticketId;
	}
	vector<int> getLineNumbers() {
		return lineNumbers;
	}
	void setTicketId(int id) {
		ticketId = id;
	}
	void setLineNumbers(vector<int> nums) {
		lineNumbers = nums;
	}
};