## MCBE Hopper Fix

**This is more vanilla than MOJANG**

When a hopper tries to collect item entities on top of it, it will fetch all the item entities in a specific AABB, and it will only try to pull the first item stack, which causes the hopper bug.

This fix modifies the code of collecting item entities, and selects a random item entity instead of the first one.

## How to use
This a dll mod, you need to inject it into BDS
