// https://leetcode.com/problems/majority-element/description/
class Solution {
public:
    int majorityElement(vector<int>& nums) 
    {
        int count = 0;
        int majElement;
        for(int i=0;i<nums.size();i++)
        {
            if(count == 0)
                majElement = nums[i];
            if(majElement == nums[i])
                count++;
            else
                count--;
        }
        return majElement;
    }
};
