//
// Created by carlo on 13/04/2025.
//

void exhaustive(OutputData &output, Algorithm &data) {
    int n = data.pallets.size();
    int maxProfit = 0;
    vector<Pallet> bestCombination;
    int totalChecked = 0;

    for (int mask = 0; mask < (1 << n); ++mask) {
        int totalWeight = 0;
        int totalProfit = 0;
        vector<Pallet> currentCombination;

        cout << "Checking combination: ";

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                cout << "1";
                totalWeight += data.pallets[i].weight;
                totalProfit += data.pallets[i].profit;
                currentCombination.push_back(data.pallets[i]);
            } else {
                cout << "0";
            }
        }

        cout << " | Weight: " << totalWeight
             << " | Profit: " << totalProfit << endl;

        if (totalWeight <= data.TotalWeight && totalProfit > maxProfit) {
            maxProfit = totalProfit;
            bestCombination = currentCombination;
        }

        totalChecked++;
    }

    cout << "\nTotal combinations checked: " << totalChecked
         << " (should be 2^" << n << " = " << (1 << n) << ")\n";

    output.totalProfit = maxProfit;
    output.pallets = bestCombination;

    cout << "\nBest combination found:\n";
    for (const auto &p : output.pallets) {
        cout << "Pallet ID: " << p.id << " | Weight: " << p.weight << " | Profit: " << p.profit << endl;
    }
    cout << "Max Profit: " << output.totalProfit << endl;
}


