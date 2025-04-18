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

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                totalWeight += data.pallets[i].weight;
                totalProfit += data.pallets[i].profit;
                currentCombination.push_back(data.pallets[i]);
            }
        }


        if (totalWeight <= data.TotalWeight && totalProfit > maxProfit) {
            maxProfit = totalProfit;
            bestCombination = currentCombination;
        }

        totalChecked++;
    }


    output.totalProfit = maxProfit;
    output.pallets = bestCombination;

}


