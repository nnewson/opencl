#include <array>
#include <iostream>
#include <random>

#include "clDevice.h"

int main(int argc, char** argv)
{
	// Setup the random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution< float > dist(-10.0f, 10.f);

	// Generate a bunch of random spreads between -10 and 10
	const size_t count = 1024;
	std::array< float, count > spreads;

	for (auto& item : spreads)
	{
		item = dist(gen);
	}

	// Create device and kernel
	clDevice device(strFile("kernel.cl"));
	auto& kernel = device.createKernel("square");
	
	// Create the various device buffers and host data
	auto& spreadBuffer = device.createBuffer(sizeof(spreads));

	std::array< float, count > bidResults; 
	auto& bidBuffer = device.createBuffer(sizeof(bidResults));

	std::array< float, count > askResults;
	auto& askBuffer = device.createBuffer(sizeof(askResults));

	std::array< unsigned char, count > backwardatedResults;
	auto& backwardatedBuffer = device.createBuffer(sizeof(backwardatedResults));

	// Bind buffers and constants to the kernel arguments
	auto bid = 100.0f;
	kernel.bindConstant(&bid, sizeof(bid), 0);
	auto ask = 105.0f;
	kernel.bindConstant(&ask, sizeof(ask), 1);

	kernel.bindBuffer(spreadBuffer, 2);
	kernel.bindConstant(&count, sizeof(count), 3);
	kernel.bindBuffer(bidBuffer, 4);
	kernel.bindBuffer(askBuffer, 5);
	kernel.bindBuffer(backwardatedBuffer, 6);
    
	// Write spread data to input buffers
	spreadBuffer.write(spreads.data(), sizeof(spreads));

	// Run the kernel and wait for it to finish
	kernel.run(count);
	kernel.join();

	// Read all the values back from the output buffers
	bidBuffer.read(bidResults.data(), sizeof(bidResults));
	askBuffer.read(askResults.data(), sizeof(askResults));
	backwardatedBuffer.read(backwardatedResults.data(), sizeof(backwardatedResults));

    // Validate our results
    for(size_t i = 0; i < count; i++)
    {
		auto correctBid = bid - spreads[i];
		if (correctBid != bidResults[i])
		{
			std::cout << "Incorrect bid for item " << i << ".  Correct bid is " << correctBid << " and calculated bid is " << bidResults[i] << std::endl;
 		}

		auto correctAsk = ask + spreads[i];
		if (correctAsk != askResults[i])
		{
			std::cout << "Incorrect ask for item " << i << ".  Correct ask is " << correctAsk << " and calculated ask is " << askResults[i] << std::endl;
		}

		if (correctBid >= correctAsk && backwardatedResults[i] == 0)
		{
			std::cout << "Item " << i << " isn't marked as backwardated and it should be." << std::endl;
		}
		else if (correctBid < correctAsk && backwardatedResults[i] == 1)
		{
			std::cout << "Item " << i << " is marked as backwardated and it shouldn'y be." << std::endl;
		}
    }

	std::cout << "Finished." << std::endl;
    return 0;
}
