#include <array>
#include <filesystem>
#include <print>
#include <random>

#include "clDevice.hpp"
#include "strFile.hpp"

int main(int argc, char** argv)
{
    // Setup the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-10.0f, 10.f);

    // Generate a bunch of random spreads between -10 and 10
    const uint32_t count = 1024;
    std::array<float, count> spreads{};

    for (auto& item : spreads)
    {
        item = dist(gen);
    }

    // Create device and kernel
#ifdef __linux__
    auto execPath = std::filesystem::canonical("/proc/self/exe");
#else
    auto execPath = std::filesystem::path(argv[0]);
#endif
    auto kernelPath = execPath.parent_path() / "kernel.cl";
    clDevice device(readFile(kernelPath));
    auto& kernel = device.createKernel("square");

    // Create the various device buffers and host data
    auto& spreadBuffer = device.createBuffer(sizeof(spreads));

    std::array<float, count> bidResults{};
    auto& bidBuffer = device.createBuffer(sizeof(bidResults));

    std::array<float, count> askResults{};
    auto& askBuffer = device.createBuffer(sizeof(askResults));

    std::array<unsigned char, count> backwardatedResults{};
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
    for (size_t i = 0; i < count; i++)
    {
        auto correctBid = bid - spreads[i];
        if (correctBid != bidResults[i])
        {
            std::println("Incorrect bid for item {}.  Correct bid is {} and calculated bid is {}", i, correctBid, bidResults[i]);
        }
        else
        {
            std::println("Correct bid for item {}.  Correct bid is {} and calculated bid is {}", i, correctBid, bidResults[i]);
        }

        auto correctAsk = ask + spreads[i];
        if (correctAsk != askResults[i])
        {
            std::println("Incorrect ask for item {}.  Correct ask is {} and calculated ask is {}", i, correctAsk, askResults[i]);
        }
        else
        {
            std::println("Correct ask for item {}.  Correct ask is {} and calculated ask is {}", i, correctAsk, askResults[i]);
        }

        if (correctBid >= correctAsk && backwardatedResults[i] == 0)
        {
            std::println("Item {} isn't marked as backwardated and it should be.", i);
        }
        else if (correctBid < correctAsk && backwardatedResults[i] == 1)
        {
            std::println("Item {} is marked as backwardated and it shouldn't be.", i);
        }
        else
        {
            std::println("Item {} is correctly marked as {}.", i,
                         backwardatedResults[i] == 1 ? "backwardated" : "not backwardated");
        }
    }

    std::println("Finished.");
    return 0;
}
