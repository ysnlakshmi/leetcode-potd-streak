/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    std::vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        
        int firstIndex = -1;
        int lastIndex = -1;
        int minDist = INT_MAX;
        int index = 2; 
        
        while (curr->next != nullptr) {
            int pVal = prev->val;
            int cVal = curr->val;
            int nVal = curr->next->val;
            
            if ((cVal > pVal && cVal > nVal) || (cVal < pVal && cVal < nVal)) {
                if (firstIndex == -1) {
                    firstIndex = index;
                } else {
                    minDist = std::min(minDist, index - lastIndex);
                }
                lastIndex = index;
            }
            
            prev = curr;
            curr = curr->next;
            index++;
        }
        
        if (firstIndex == -1 || firstIndex == lastIndex) {
            return {-1, -1};
        }
        
        int maxDist = lastIndex - firstIndex;
        return {minDist, maxDist};
    }
};