##MCBE Hopper Fix##

(May be not vanilla)
When a hopper tries to collect item entities on top of it, it will fetch all the item entities in a specific AABB, and it will only try to pull the first item stack, which causes the hopper bug.

This fix modifies the code of collecting item entities, and selects a random item entity instead of the first one.
