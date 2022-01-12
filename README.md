# Shopify 2022 Internship Backend Development Challenge
Hello! If you're seeing this you're likely here to evaluate my submission. If you're unfamiliar with c++ and don't have a local IDE with which to run CPP files,
rather than go through that arduous labor, simply visit an online C++ compiler and paste the shopifyCRUD.cpp file. I personally use https://www.onlinegdb.com/online_c++_compiler. Otherwise, I've included the full folder with the Visual Studio Solution. This contains an identical C++ file to execute.


The project gives a description on how to add, edit, and create a CSV file of the inventory. I elected to use C++, as I figure it would be a unique take as opposed to using python and pandas. I also wanted to try and create the most efficient program in terms of space time complexity. 

To hold our inventory, we use a map with keys corresponding to the name of each item, and a pointer to where the item is stored on the heap. We use this so that we only need to make 1 item object for each different item. 

Issues:
1. This doesn't support viewing items named 'all' for the sake of convenience to the user
2. I probably should go back and make a 'delete' function to completely remove an item from stock -- DONE! 1/12/22
3. Trying to create a new item with the same name but different sku will overwrite the existing item
4. No front end UI/UX. If I made a python flask app with pandas, probably might've been easier to do so with Djinja II and what not
