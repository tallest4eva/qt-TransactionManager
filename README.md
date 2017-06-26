=====================
TransactionManager
=====================

Transaction Manager app implemented in Qt
=====================
1.09 - 2017-06-23:
Improvements:
General:
- DONE  - Potentially reduce dlls like icu*.dll. Need to use Qt build without ICU:
            http://doc.qt.io/qt-5/windows-deployment.html#application-dependencies
- DONE  - Revamp tags to be dynamic like sub categories
- DONE  - Add Transfers to Categories.
- DONE  - Make Categories act like real checkboxes (not Radio Buttons)
- DONE  - How do I handle exclude Labels in match labels?
Accounts:
- DONE  - Don't lighten account text on highlighted, Maybe add white text-shadow and don't change.
- DONE  - Add Dropdown under "Show Closed Accounts" to sort Accounts by Name, Amount, Open/Close Date.
- DONE  - Instead of Present, show last transaction date. The Open and not highlighted should be enough to determine
- DONE  - Added transaction count to Account list item
Transactions:
- DONE  - Add hover text over transaction after 3 secs to show transaction details etc
Reports:
- DONE 	- In Reports, Add checkbox to display transfer transactions in tables, graphs
- DONE 	- Add tab for account net worths line graphs in different colors
- DONE  - Show net income checkflag enabled by default.
- DONE  - Show net income in Month bubble.
- DONE  - Add Show Filter in Transactions and Show Filter in Reports, Allows Reports to be filtered by search tag too.
- DONE  - Allow Sort Report List by all columns.
- DONE  - Add dropdown boxes to sort Pie Chart items underneath by Name, Amount Descending and Ascending.
- DONE  - Try again to Make the Pie Chart text color be green, red and try to add commas to numbers (right justify).
- DONE  - Add totals to Pie Charts? ABANDONED because popup shows total
=====================

=====================
