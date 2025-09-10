// https://leetcode.com/problems/move-zeroes/description/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        int current_index = 0;
        for(int i=0;i<size;i++)
        {
            if (nums[i] != 0)
            {
                nums[current_index] = nums[i];
                current_index++;
            }
        }
        for(int i=current_index;i<size;i++)
            nums[i] = 0;
    }
};
