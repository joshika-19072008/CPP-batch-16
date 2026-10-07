#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Abstract Base Class
class Employee
{
protected:
    int employeeId;
    string name;
    string department;
    string designation;
    double basicSalary;

public:
    Employee(int id, string n, string dept, string desig, double basic)
    {
        employeeId = id;
        name = n;
        department = dept;
        designation = desig;
        basicSalary = basic;
    }

    virtual double calculateAllowance() const = 0;
    virtual double calculateDeduction() const = 0;
    virtual string getEmployeeType() const = 0;

    int getEmployeeId() const
    {
        return employeeId;
    }

    double getGrossSalary() const
    {
        return basicSalary + calculateAllowance();
    }

    double getNetSalary() const
    {
        return getGrossSalary() - calculateDeduction();
    }

    void displayPayslip() const
    {
        cout << "\n============================================\n";
        cout << "              EMPLOYEE PAYSLIP\n";
        cout << "============================================\n";

        cout << "Employee ID       : " << employeeId << endl;
        cout << "Employee Name     : " << name << endl;
        cout << "Employee Type     : " << getEmployeeType() << endl;
        cout << "Department        : " << department << endl;
        cout << "Designation       : " << designation << endl;

        cout << "--------------------------------------------\n";

        cout << fixed << setprecision(2);

        cout << "Basic Salary      : Rs. " << basicSalary << endl;
        cout << "Allowances        : Rs. "
             << calculateAllowance() << endl;

        cout << "Gross Salary      : Rs. "
             << getGrossSalary() << endl;

        cout << "Deductions        : Rs. "
             << calculateDeduction() << endl;

        cout << "--------------------------------------------\n";

        cout << "Net Salary        : Rs. "
             << getNetSalary() << endl;

        cout << "============================================\n";
    }

    virtual ~Employee()
    {
    }
};


// Permanent Employee
class PermanentEmployee : public Employee
{
private:
    double bonus;

public:
    PermanentEmployee(int id, string n, string dept,
                      string desig, double basic, double b)
        : Employee(id, n, dept, desig, basic)
    {
        bonus = b;
    }

    double calculateAllowance() const
    {
        double hra = basicSalary * 0.20;
        double da = basicSalary * 0.10;

        return hra + da + bonus;
    }

    double calculateDeduction() const
    {
        return basicSalary * 0.12;
    }

    string getEmployeeType() const
    {
        return "Permanent";
    }
};


// Contract Employee
class ContractEmployee : public Employee
{
private:
    double transportAllowance;

public:
    ContractEmployee(int id, string n, string dept,
                     string desig, double basic, double transport)
        : Employee(id, n, dept, desig, basic)
    {
        transportAllowance = transport;
    }

    double calculateAllowance() const
    {
        return transportAllowance;
    }

    double calculateDeduction() const
    {
        return basicSalary * 0.05;
    }

    string getEmployeeType() const
    {
        return "Contract";
    }
};


// Add Employee
void addEmployee(vector<Employee*>& employees)
{
    int id;
    string name;
    string department;
    string designation;
    double basicSalary;
    int type;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Designation: ";
    getline(cin, designation);

    cout << "Enter Basic Salary: ";
    cin >> basicSalary;

    cout << "\n1. Permanent Employee";
    cout << "\n2. Contract Employee";
    cout << "\nEnter Employee Type: ";
    cin >> type;

    if (type == 1)
    {
        double bonus;

        cout << "Enter Bonus: ";
        cin >> bonus;

        employees.push_back(
            new PermanentEmployee(
                id, name, department,
                designation, basicSalary, bonus
            )
        );

        cout << "\nPermanent Employee added successfully!\n";
    }
    else if (type == 2)
    {
        double transport;

        cout << "Enter Transport Allowance: ";
        cin >> transport;

        employees.push_back(
            new ContractEmployee(
                id, name, department,
                designation, basicSalary, transport
            )
        );

        cout << "\nContract Employee added successfully!\n";
    }
    else
    {
        cout << "\nInvalid employee type!\n";
    }
}


// Display All Employees
void displayAllEmployees(vector<Employee*>& employees)
{
    if (employees.empty())
    {
        cout << "\nNo employee records available.\n";
        return;
    }

    cout << "\n====================================================\n";
    cout << "                 ALL EMPLOYEES\n";
    cout << "====================================================\n";

    for (int i = 0; i < employees.size(); i++)
    {
        employees[i]->displayPayslip();
    }
}


// Search Employee
Employee* searchEmployee(vector<Employee*>& employees, int id)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (employees[i]->getEmployeeId() == id)
        {
            return employees[i];
        }
    }

    return NULL;
}


// Generate Payslip
void generatePayslip(vector<Employee*>& employees)
{
    int id;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    Employee* emp = searchEmployee(employees, id);

    if (emp != NULL)
    {
        emp->displayPayslip();
    }
    else
    {
        cout << "\nEmployee not found!\n";
    }
}


// Payroll Report
void payrollReport(vector<Employee*>& employees)
{
    if (employees.empty())
    {
        cout << "\nNo employee records available.\n";
        return;
    }

    double totalBasic = 0;
    double totalGross = 0;
    double totalDeduction = 0;
    double totalNet = 0;

    for (int i = 0; i < employees.size(); i++)
    {
        totalGross += employees[i]->getGrossSalary();
        totalNet += employees[i]->getNetSalary();
        totalDeduction += employees[i]->calculateDeduction();

        totalBasic +=
            employees[i]->getGrossSalary()
            - employees[i]->calculateAllowance();
    }

    cout << "\n============================================\n";
    cout << "             PAYROLL REPORT\n";
    cout << "============================================\n";

    cout << fixed << setprecision(2);

    cout << "Number of Employees : "
         << employees.size() << endl;

    cout << "Total Basic Salary  : Rs. "
         << totalBasic << endl;

    cout << "Total Gross Salary  : Rs. "
         << totalGross << endl;

    cout << "Total Deductions    : Rs. "
         << totalDeduction << endl;

    cout << "Total Net Salary    : Rs. "
         << totalNet << endl;

    cout << "============================================\n";
}


// Main Function
int main()
{
    vector<Employee*> employees;

    int choice;

    do
    {
        cout << "\n\n============================================\n";
        cout << "       EMPLOYEE PAYROLL MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Generate Payslip\n";
        cout << "5. Payroll Report\n";
        cout << "6. Exit\n";

        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addEmployee(employees);
            break;

        case 2:
            displayAllEmployees(employees);
            break;

        case 3:
        {
            int id;

            cout << "\nEnter Employee ID: ";
            cin >> id;

            Employee* emp = searchEmployee(employees, id);

            if (emp != NULL)
            {
                emp->displayPayslip();
            }
            else
            {
                cout << "\nEmployee not found!\n";
            }

            break;
        }

        case 4:
            generatePayslip(employees);
            break;

        case 5:
            payrollReport(employees);
            break;

        case 6:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid menu choice!\n";
        }

    } while (choice != 6);


    // Free memory
    for (int i = 0; i < employees.size(); i++)
    {
        delete employees[i];
    }

    return 0;
}
