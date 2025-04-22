//
// Created by carlo on 13/04/2025.
//

void weight_used(OutputData &output) {
    for (auto p : output.pallets) {
       output.totalWeight += p.weight;
    }
}

void exhaustive(OutputData &output, Algorithm &data) {
    int n = data.pallets.size();
    int maxProfit = 0;
    vector<Pallet> bestCombination;

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

    }


    output.totalProfit = maxProfit;
    output.pallets = bestCombination;

}


