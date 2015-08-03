/**
 *  Author:
 *    Wu Qi <qi.wu@cern.ch>
 *
 *  allpix Authors:
 *   John Idarraga <idarraga@cern.ch>
 *   Mathieu Benoit <Mathieu.Benoit@cern.ch>
 */

#include "AllPixQiWuDigit.hh"

G4Allocator<AllPixQiWuDigit> AllPixQiWuDigitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

AllPixQiWuDigit::AllPixQiWuDigit()
{
	pixelIDX = -1;
	pixelIDY = -1;
	pixelCounts = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

AllPixQiWuDigit::~AllPixQiWuDigit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

AllPixQiWuDigit::AllPixQiWuDigit(const AllPixQiWuDigit& right)
: AllPixDigitInterface()
{
	pixelIDX = right.pixelIDX;
	pixelIDY = right.pixelIDY;
	pixelCounts = right.pixelCounts;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const AllPixQiWuDigit& AllPixQiWuDigit::operator=(const AllPixQiWuDigit& right)
{

	pixelIDX = right.pixelIDX;
	pixelIDY = right.pixelIDY;
	pixelCounts = right.pixelCounts;
	return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int AllPixQiWuDigit::operator==(const AllPixQiWuDigit& right) const
		{
	return ((pixelIDX==right.pixelIDX)&&
			(pixelIDY==right.pixelIDY)&&
			(pixelCounts==right.pixelCounts));
		}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void AllPixQiWuDigit::Draw()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void AllPixQiWuDigit::Print()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
