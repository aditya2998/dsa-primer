// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int uniqueElements = 0;
        for(int currentIndex = 1; currentIndex < nums.size();currentIndex++)
        {
            if(nums[currentIndex] != nums[uniqueElements])
            {
                uniqueElements++;
                nums[uniqueElements] = nums[currentIndex];
            }
        }
        return uniqueElements+1;
    }
};
