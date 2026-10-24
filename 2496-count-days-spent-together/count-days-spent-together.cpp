class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        auto getDays = [](string date) {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int totalDays = day;
            for (int i = 0; i < month - 1; ++i) {
                totalDays += daysInMonths[i];
            }
            return totalDays;
        };
        
        int arrA = getDays(arriveAlice);
        int levA = getDays(leaveAlice);
        int arrB = getDays(arriveBob);
        int levB = getDays(leaveBob);
        
        int startOverlap = max(arrA, arrB);
        int endOverlap = min(levA, levB);
        
        if (startOverlap <= endOverlap) {
            return endOverlap - startOverlap + 1;
        }
        return 0;
    }
};