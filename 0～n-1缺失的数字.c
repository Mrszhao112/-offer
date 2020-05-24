//一个长度为n-1的递增排序数组中的所有数字都是唯一的，
//并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        // 如果这个数在中间[0,1,3]
        int res = recursion(nums,0,n-1);
        if(res != -1) 
        {
          return res;
        }
        // 排除[0,1,2]与[1,2,3]有序结果
        return nums[0] == 0 ? nums[n-1]+1 : 0;   
    }
    int recursion(vector<int>& nums,int left,int right) {
        if(left>right) 
        {
          return -1;
        }
        int mid = left + (right-left) / 2;
        if(mid+1 < nums.size() && nums[mid] + 2 == nums[mid+1])
        {
          return nums[mid]+1;
        
        }
        int res1 = recursion(nums,left,mid-1);
        int res2 = recursion(nums,mid+1,right);
        if(res1 == -1)
        {
          return res2;
        }
        return res1;
    }
};
